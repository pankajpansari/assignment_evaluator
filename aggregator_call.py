import os
from pathlib import Path
from typing import Any, Dict
from openai import OpenAI

CONFIG = {
    'assignment_name' : 'cs61_pset0',
    'parameter' : 'efficiency',
    'model' : 'gpt-4o',
}

# File paths
BASE_PATH = Path('assignments')
PROBLEM_PATH = BASE_PATH / CONFIG['assignment_name'] / 'problem' / 'sort_argument.txt'
SOLUTION_PATH = BASE_PATH / CONFIG['assignment_name'] / 'submissions' / 'sub_1' / 'sortargs61.cc'
SYSTEM_PROMPT_PATH = BASE_PATH / 'generic_prompts' / 'system_aggregator.txt'
PROPOSAL_PATH = BASE_PATH / CONFIG['assignment_name'] / 'submissions' / 'sub_1' / 'output'

def get_client() -> Any:
   if CONFIG['model'].startswith('claude'):
       return Anthropic()
   elif CONFIG['model'].startswith('gpt'):
       return OpenAI()
   else:
       return Together() 


def read_file(file_path: Path) -> str:
    with open(file_path, 'r') as f:
        return f.read()
    
def create_message_content() -> str:
    problem_statement = read_file(PROBLEM_PATH)
    program_solution = read_file(SOLUTION_PATH)
    feedback_claude = read_file(PROPOSAL_PATH / 'proposer_claude_efficiency.txt') 
    feedback_mixtral = read_file(PROPOSAL_PATH / 'proposer_mixtral_efficiency.txt') 
    feedback_llama = read_file(PROPOSAL_PATH / 'proposer_llama_efficiency.txt') 
    feedback_gpt = read_file(PROPOSAL_PATH / 'proposer_gpt_efficiency.txt') 

    return (f"Problem statement : {problem_statement}\n\n"
            f"Code to evaluate : {program_solution}\n\n"
            f"Parameter to assess : {CONFIG['parameter']}\n\n"
            f"Feedback 1: {feedback_claude} \n\n"
            f"Feedback 2: {feedback_mixtral} \n\n"
            f"Feedback 3: {feedback_llama} \n\n"
            f"Feedback 4: {feedback_gpt}")

# Read in the system prompt
def get_model_response(client: Any) -> Dict[str, Any]:
    system_prompt = read_file(SYSTEM_PROMPT_PATH)
    message_content = create_message_content()

    if isinstance(client, Anthropic):
        return client.messages.create(
            model = CONFIG['model'],
            max_tokens = 1000,
            temperature = 0.0,
            system = system_prompt,
            messages = [{"role": "user", "content": message_content}],
        )
    else:
        return client.chat.completions.create(
            model = CONFIG['model'], 
            messages = [ 
                {"role": "system", "content": system_prompt},
                {"role": "user", "content": message_content},
           ],
        )

def write_output(response: Dict[str, Any]):
    output_file = BASE_PATH / CONFIG['assignment_name'] / 'submissions' / 'sub_1' / 'output' / f"aggregator_{CONFIG['model']}_{CONFIG['parameter']}.txt"

    if isinstance(client, Anthropic):
        content = response.content[0].text
    else:
        content = response.choices[0].message.content

    os.makedirs(output_file.parent, exist_ok=True)
    with open(output_file, 'w', encoding = 'utf-8') as f:
        f.write(f"{CONFIG['model']}\n")
        f.write(f"{CONFIG['assignment_name']}\n")
        f.write(f"{CONFIG['parameter']}\n")
        f.write(content)

if __name__ == '__main__':
    client = get_client()
    response = get_model_response(client)
    write_output(response)