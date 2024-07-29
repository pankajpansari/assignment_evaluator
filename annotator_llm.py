from base_llm import BaseLLM
from config_loader import CONFIG

class AnnotatorLLM(BaseLLM):
    def __init__(self, model: dict, parameter: dict):
        super().__init__(model, parameter)
        self.system_prompt_path = self.base_path / 'generic_prompts' / f"{CONFIG['annotator']['system_prompt']}" 
        self.parameter_prompt_path = self.base_path / 'generic_prompts' / f"{parameter['prompt_file']}"
        self.output_filename = f"annotator_{model['type']}_{parameter['name']}.txt"

    def create_message_content(self) -> str:
        problem_statement = self.read_file(self.problem_path)
        program_solution = self.read_file(self.solution_path)
        aggregate_feedback = self.read_file(self.output_path / f"aggregator_{CONFIG['aggregator']['model']['type']}_{self.parameter}.txt")

        return (f"Problem statement : {problem_statement}\n\n"
                f"Code to evaluate : {program_solution}\n\n"
                f"Feedback : {aggregate_feedback} \n\n")