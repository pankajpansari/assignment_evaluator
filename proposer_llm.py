from base_llm import BaseLLM
from config_loader import CONFIG

class ProposerLLM(BaseLLM):
    def __init__(self, model: dict, parameter: dict):
        super().__init__(model, parameter)
        self.parameter_prompt_path = self.base_path / 'generic_prompts' / f"{parameter['prompt_file']}"
        self.system_prompt_path = self.base_path / 'generic_prompts' / f"{CONFIG['proposers']['system_prompt']}"
        self.output_filename = f"proposer_{model['type']}_{parameter['name']}.txt"

    def create_message_content(self) -> str:
        problem_statement = self.read_file(self.problem_path)
        program_solution = self.read_file(self.solution_path)
        parameter_prompt = self.read_file(self.parameter_prompt_path)

        return (f"Problem statement : {problem_statement}\n\n"
                f"Code to evaluate : {program_solution}\n\n"
                f"Parameter to assess : {parameter_prompt}")