from base_llm import BaseLLM
from config_loader import CONFIG 
from pathlib import Path

class AnnotatorLLM(BaseLLM):
    def __init__(self, model: dict, parameter: dict):
        super().__init__(model, parameter)
        self.system_prompt_path = f"{CONFIG['annotator']['system_prompt']}" 
        self.parameter_prompt_path = f"{parameter['prompt_file']}"
        output_prefix = CONFIG['assignment']['problem_file'].split('/')[1].split('.')[0]  
        self.output_filename = f"{output_prefix}_annotator_{model['type']}_{parameter['name']}.txt"

    def create_message_content(self) -> str:
        problem_statement = self.read_file(self.problem_path)
        program_solution = self.read_file(self.solution_path)
        output_prefix = CONFIG['assignment']['problem_file'].split('/')[1].split('.')[0]  
        aggregate_feedback = self.read_file(Path(self.output_path) / f"{output_prefix}_aggregator_{CONFIG['aggregator']['model']['type']}_{self.parameter}.txt")

        return (f"Problem statement : {problem_statement}\n\n"
                f"Code to evaluate : {program_solution}\n\n"
                f"Feedback : {aggregate_feedback} \n\n")