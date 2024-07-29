from base_llm import BaseLLM
from config_loader import CONFIG

class AggregatorLLM(BaseLLM):
    def __init__(self, model: dict, parameter: dict):
        super().__init__(model, parameter)
        self.system_prompt_path = self.base_path / 'generic_prompts' / f"{CONFIG['aggregator']['system_prompt']}"
        self.output_filename = f"aggregator_{model['type']}_{self.parameter}.txt"
   
    def create_message_content(self) -> str:
        problem_statement = self.read_file(self.problem_path)
        program_solution = self.read_file(self.solution_path)

        proposals = []
        for model in CONFIG['proposers']['models']:
            proposals.append(self.read_file(self.output_path / f"proposer_{model['type']}_{self.parameter}.txt"))

        proposal_prompt = ''
        for i, proposal in enumerate(proposals):
            proposal_prompt += f"Proposer {i}: {proposal}\n\n"

        return (f"Problem statement : {problem_statement}\n\n"
                f"Code to evaluate : {program_solution}\n\n"
                f"Parameter to assess : {self.parameter}\n\n"  # no parameter prompt; parameter name is enough
                f"{proposal_prompt}")