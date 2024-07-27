from base_llm import BaseLLM

class AggregatorLLM(BaseLLM):
    def __init__(self, config):
        super().__init__(config)
        self.system_prompt_path = self.base_path / 'generic_prompts' / 'system_aggregator.txt'
        model = ''
        if self.config['model'].startswith('claude'):
            model = 'claude'
        self.output_filename = f"aggregator_{model}_{self.config['parameter']}.txt"
        self.proposal_path = self.base_path / self.config['assignment_name'] / 'submissions' / 'sub_1' / 'output'
   
    def create_message_content(self) -> str:
        problem_statement = self.read_file(self.problem_path)
        program_solution = self.read_file(self.solution_path)
        feedback_claude = self.read_file(self.proposal_path / 'proposer_claude_efficiency.txt') 
        feedback_mixtral = self.read_file(self.proposal_path / 'proposer_mixtral_efficiency.txt') 
        feedback_llama = self.read_file(self.proposal_path / 'proposer_llama_efficiency.txt') 
        #feedback_gpt = self.read_file(self.proposal_path / 'proposer_gpt_efficiency.txt') 

        return (f"Problem statement : {problem_statement}\n\n"
                f"Code to evaluate : {program_solution}\n\n"
                f"Parameter to assess : {self.config['parameter']}\n\n"  # no parameter prompt; parameter name is enough
                f"Feedback 1: {feedback_claude} \n\n"
                f"Feedback 2: {feedback_mixtral} \n\n"
                f"Feedback 3: {feedback_llama} \n\n")
#                f"Feedback 4: {feedback_gpt}")

if __name__ == '__main__':
    config = {
        'model' : 'claude-3-5-sonnet-20240620',
        'parameter' : 'efficiency',
        'assignment_name' : 'cs61_pset0',
    }
    aggregator = AggregatorLLM(config)
    aggregator.run() 