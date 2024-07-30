import os
import logging
from pathlib import Path
from typing import Any, Dict
from anthropic import Anthropic
from openai import OpenAI
from together import Together
from config_loader import CONFIG
from pathlib import Path

logging = logging.getLogger(__name__)

class BaseLLM:
    def __init__(self, model: dict, parameter: dict):
        self.model = model
        self.parameter = parameter['name']
        self.problem_path = CONFIG['assignment']['problem_file']
        self.solution_path = CONFIG['assignment']['solution_file']
        self.output_path = CONFIG['assignment']['output_path']
        os.makedirs(self.output_path, exist_ok=True)

    def get_client(self) -> Any:
       if self.model['name'].startswith('claude'):
           return Anthropic()
       elif self.model['name'].startswith('gpt'):
           return OpenAI()
       else:
           return Together() 


    def read_file(self, file_path: Path) -> str:
        try:
            with open(file_path, 'r') as f:
                return f.read()
        except FileNotFoundError:
            logger.error(f"File not found: {file_path}")
            raise
    
    def create_message_content(self) -> str:
        raise NotImplementedError("Subclasses must implement this method")
    
    def get_model_response(self, client: Any) -> Dict[str, Any]:
        system_prompt = self.read_file(self.system_prompt_path)
        message_content = self.create_message_content()

        if isinstance(client, Anthropic):
            return client.messages.create(
                model = self.model['name'],
                max_tokens = 1000,
                temperature = 0.0,
                system = system_prompt,
                messages = [{"role": "user", "content": message_content}],
            )
        else:
            return client.chat.completions.create(
                model = self.model['name'], 
                messages = [ 
                    {"role": "system", "content": system_prompt},
                    {"role": "user", "content": message_content},
               ],
            )

    def write_output(self, response: Dict[str, Any], output_filename: str):
        output_file = Path(self.output_path) / output_filename 
        if isinstance(self.get_client(), Anthropic):
            content = response.content[0].text
        else:
            content = response.choices[0].message.content

        os.makedirs(output_file.parent, exist_ok=True)
        with open(output_file, 'w', encoding = 'utf-8') as f:
            f.write(f"{self.model['name']}\n")
            f.write(f"{self.parameter}\n")
            f.write(content)

    def run(self):
        client = self.get_client()
        response = self.get_model_response(client)
        self.write_output(response, self.output_filename)