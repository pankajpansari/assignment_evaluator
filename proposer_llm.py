import os
from pathlib import Path

from base_llm import BaseLLM
from utils import CONFIG 

class ProposerLLM(BaseLLM):
    def __init__(self, model: dict, parameter: dict):
        super().__init__(model, parameter)
        self.parameter_prompt_path = f"{parameter['prompt_file']}"
        self.system_prompt_path = f"{CONFIG['proposers']['system_prompt']}"
        output_prefix = CONFIG['assignment']['problem_file'].split('/')[1].split('.')[0]  
        self.output_path = CONFIG['assignment']['intermediate_path']
        if not os.path.exists(self.output_path):
            os.makedirs(self.output_path)
        self.output_filename = f"{output_prefix}_proposer_{model['type']}_{parameter['name']}.txt"

    def create_message_content(self) -> str:
        problem_statement = self.read_file(self.problem_path)
        program_solution = self.read_file(self.solution_path)
        parameter_prompt = self.read_file(self.parameter_prompt_path)

        return (f"<problem> {problem_statement} </problem> \n\n"
                f"<code> {program_solution} </code> \n\n"
                f"<instructions> {parameter_prompt} </instructions>")