import os
from pathlib import Path

from base_llm import BaseLLM
from utils import CONFIG 

class AnnotatorLLM(BaseLLM):
    def __init__(self, model, parameter):
        super().__init__(model, parameter)
        self.system_prompt_path = f"{CONFIG['annotator']['system_prompt']}" 
        self.parameter_prompt_path = f"{parameter['prompt_file']}"
        output_prefix = CONFIG['assignment']['problem_file'].split('/')[1].split('.')[0]  
        self.output_path = CONFIG['assignment']['intermediate_path']
        if not os.path.exists(self.output_path):
            os.makedirs(self.output_path)
        self.output_filename = f"{output_prefix}_annotator_{model['type']}_{parameter['name']}.txt"

    def create_message_content(self):
        problem_statement = self.read_file(self.problem_path)
        program_solution = self.read_file(self.solution_path)
        output_prefix = CONFIG['assignment']['problem_file'].split('/')[1].split('.')[0]  
        aggregate_feedback = self.read_file(Path(CONFIG['assignment']['intermediate_path']) / f"{output_prefix}_aggregator_{CONFIG['aggregator']['model']['type']}_{self.parameter}.txt")

        return (f"<problem> {problem_statement} </problem> \n\n"
                f"<code> {program_solution} </code> \n\n"
                f"<data> {aggregate_feedback} </data> \n\n")
