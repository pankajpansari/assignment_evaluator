import os
import pathlib

import anthropic
import openai
import together

import utils

class BaseLLM:
    def __init__(self, model, parameter):
        self.model = model
        self.parameter = parameter['name']
        self.problem_path = utils.CONFIG['assignment']['problem_file']
        self.solution_path = utils.CONFIG['assignment']['solution_file']
        self.output_path = utils.CONFIG['assignment']['output_path']
        os.makedirs(self.output_path, exist_ok=True)

    def get_client(self):
       if self.model['name'].startswith('claude'):
           return anthropic.Anthropic()
       elif self.model['name'].startswith('gpt'):
           return openai.OpenAI()
       else:
           return together.Together() 


    def read_file(self, file_path):
        with open(file_path, 'r') as f:
            return f.read()
    
    def create_message_content(self):
        raise NotImplementedError("Subclasses must implement this method")
    
    def get_model_response(self, client):
        system_prompt = self.read_file(self.system_prompt_path)
        message_content = self.create_message_content()

        if isinstance(client, anthropic.Anthropic):
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

    def write_output(self, response, output_filename):
        output_file = pathlib.Path(self.output_path) / output_filename 
        if isinstance(self.get_client(), anthropic.Anthropic):
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