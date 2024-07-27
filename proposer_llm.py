from base_llm import BaseLLM

class ProposerLLM(BaseLLM):
    def __init__(self, config):
        super().__init__(config)
        self.parameter_prompt_path = self.base_path / 'generic_prompts' / f"{self.config['parameter']}.txt"
        self.system_prompt_path = self.base_path / 'generic_prompts' / 'system_proposer.txt'
        model = ''
        if self.config['model'].startswith('meta-llama'):
            model = 'llama'
        elif self.config['model'].startswith('mistralai'):
            model = 'mixtral'
        elif self.config['model'].startswith('claude'):
            model = 'claude'

        self.output_filename = f"proposer_{model}_{self.config['parameter']}.txt"

    def create_message_content(self) -> str:
        problem_statement = self.read_file(self.problem_path)
        program_solution = self.read_file(self.solution_path)
        parameter_prompt = self.read_file(self.parameter_prompt_path)

        return (f"Problem statement : {problem_statement}\n\n"
                f"Code to evaluate : {program_solution}\n\n"
                f"Parameter to assess : {parameter_prompt}")

if __name__ == '__main__':
    config = {
        'model' : 'gpt-3.5-turbo',
        'parameter' : 'efficiency',
        'assignment_name' : 'cs61_pset0',
    }
    proposer = ProposerLLM(config)
    proposer.run()