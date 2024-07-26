import os
from pathlib import Path
from typing import Any, Dict
from anthropic import Anthropic
from openai import OpenAI
from together import Together

CONFIG = {
    'assignment_name' : 'cs61_pset0',
    'parameter' : 'efficiency',
#    'model' : 'claude-3-5-sonnet-20240620',
    'model' : 'meta-llama/Meta-Llama-3.1-405B-Instruct-Turbo',
#    'model' : 'mistralai/Mixtral-8x22B-Instruct-v0.1',
#    'model' : 'gpt-4o',
}

# File paths
BASE_PATH = Path('assignments')
PROBLEM_PATH = BASE_PATH / CONFIG['assignment_name'] / 'problem' / 'sort_argument.txt'
SOLUTION_PATH = BASE_PATH / CONFIG['assignment_name'] / 'submissions' / 'sub_1' / 'sortargs61.cc'
PARAMETER_PROMPT_PATH = BASE_PATH / 'generic_prompts' / f"{CONFIG['parameter']}.txt"
SYSTEM_PROMPT_PATH = BASE_PATH / 'generic_prompts' / 'system.txt'

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
    parameter_prompt = read_file(PARAMETER_PROMPT_PATH)

    return (f"Problem statement : {problem_statement}\n\n"
            f"Code to evaluate : {program_solution}\n\n"
            f"Parameter to assess : {parameter_prompt}")

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
    output_file = BASE_PATH / CONFIG['assignment_name'] / 'submissions' / 'sub_1' / 'output' / f"proposer_{CONFIG['model']}_{CONFIG['parameter']}.txt"
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