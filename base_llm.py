import os
from pathlib import Path
from typing import Any, Dict
from anthropic import Anthropic
from openai import OpenAI
from together import Together

class BaseLLM:
    def __init__(self, config):
        self.config = config
        self.base_path = Path('assignments')
        self.problem_path = self.base_path / self.config['assignment_name'] / 'problem' / 'sort_argument.txt'
        self.solution_path = self.base_path / self.config['assignment_name'] / 'submissions' / 'sub_1' / 'sortargs61.cc'
        self.output_path = self.base_path / self.config['assignment_name'] / 'submissions' / 'sub_1' / 'output'

    def get_client(self) -> Any:
       if self.config['model'].startswith('claude'):
           return Anthropic()
       elif self.config['model'].startswith('gpt'):
           return OpenAI()
       else:
           return Together() 


    def read_file(self, file_path: Path) -> str:
        with open(file_path, 'r') as f:
            return f.read()
    
    def create_message_content(self) -> str:
        raise NotImplementedError("Subclasses must implement this method")
    
    def get_model_response(self, client: Any) -> Dict[str, Any]:
        system_prompt = self.read_file(self.system_prompt_path)
        message_content = self.create_message_content()

        if isinstance(client, Anthropic):
            return client.messages.create(
                model = self.config['model'],
                max_tokens = 1000,
                temperature = 0.0,
                system = system_prompt,
                messages = [{"role": "user", "content": message_content}],
            )
        else:
            return client.chat.completions.create(
                model = self.config['model'], 
                messages = [ 
                    {"role": "system", "content": system_prompt},
                    {"role": "user", "content": message_content},
               ],
            )

    def write_output(self, response: Dict[str, Any], output_filename: str):
        output_file = self.output_path / output_filename 
        if isinstance(self.get_client(), Anthropic):
            content = response.content[0].text
        else:
            content = response.choices[0].message.content

        os.makedirs(output_file.parent, exist_ok=True)
        with open(output_file, 'w', encoding = 'utf-8') as f:
            f.write(f"{self.config['model']}\n")
            f.write(f"{self.config['assignment_name']}\n")
            f.write(f"{self.config['parameter']}\n")
            f.write(content)

    def run(self):
        client = self.get_client()
        response = self.get_model_response(client)
        self.write_output(response, self.output_filename)