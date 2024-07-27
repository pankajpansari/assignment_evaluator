from base_llm import BaseLLM

class AnnotatorLLM(BaseLLM):
    def __init__(self, config):
        super().__init__(config)
        self.system_prompt_path = self.base_path / 'generic_prompts' / 'system_annotator.txt'
        self.parameter_prompt_path = self.base_path / 'generic_prompts' / f"{self.config['parameter']}.txt"
        self.output_filename = f"annotator_{self.config['model']}_{self.config['parameter']}.txt"
        self.aggregate_path = self.base_path / self.config['assignment_name'] / 'submissions' / 'sub_1' / 'output'

    def create_message_content(self) -> str:
        problem_statement = self.read_file(self.problem_path)
        program_solution = self.read_file(self.solution_path)
        model = ''
        if self.config['model'].startswith('claude'):
            model = 'claude'
        aggregate_feedback_gpt = self.read_file(self.aggregate_path / f"aggregator_{model}_{self.config['parameter']}.txt")

        return (f"Problem statement : {problem_statement}\n\n"
                f"Code to evaluate : {program_solution}\n\n"
                f"Feedback : {aggregate_feedback_gpt} \n\n")

if __name__ == '__main__':
    CONFIG = {
        'assignment_name' : 'cs61_pset0',
        'parameter' : 'efficiency',
        'model' : 'claude-3-5-sonnet-20240620',
    }
    annotator = AnnotatorLLM(CONFIG)
    annotator.run()