from base_llm import BaseLLM
from config_loader import CONFIG 
from pathlib import Path

class AggregatorLLM(BaseLLM):
    def __init__(self, model: dict, parameter: dict):
        super().__init__(model, parameter)
        self.system_prompt_path = f"{CONFIG['aggregator']['system_prompt']}"
        output_prefix = CONFIG['assignment']['problem_file'].split('/')[1].split('.')[0]  
        self.output_filename = f"{output_prefix}_aggregator_{model['type']}_{self.parameter}.txt"
   
    def create_message_content(self) -> str:
        problem_statement = self.read_file(self.problem_path)
        program_solution = self.read_file(self.solution_path)

        proposals = []
        output_prefix = CONFIG['assignment']['problem_file'].split('/')[1].split('.')[0]  
        for model in CONFIG['proposers']['models']:
            proposals.append(self.read_file(Path(self.output_path) / f"{output_prefix}_proposer_{model['type']}_{self.parameter}.txt"))

        proposal_prompt = ''
        for i, proposal in enumerate(proposals):
            proposal_prompt += f"Proposer {i}: {proposal}\n\n"

        return (f"Problem statement : {problem_statement}\n\n"
                f"Code to evaluate : {program_solution}\n\n"
                f"Parameter to assess : {self.parameter}\n\n"  # no parameter prompt; parameter name is enough
                f"{proposal_prompt}")