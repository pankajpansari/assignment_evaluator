# Copyright (c) 2024 Pankaj Pansari 
#
# This file is part of program annotator, which is licensed under the MIT License.
# See the LICENSE file for details.
"""AnnotatorLLM class generates feedback annotations in program and a summary explanation. 

This class is used for the third and final stage of the evaluation. The output of the aggregator
is used to pin-point in the code the positive/negative aspects of implementation. A short explanation
summary of the feedback is also generated.

Typical usage example:
    
        import annotator_llm
        annotator = annotator_llm.AnnotatorLLM(model, parameter)
        annotator.run()
"""

import os
import pathlib

import base_llm
import utils

class AnnotatorLLM(base_llm.BaseLLM):
    def __init__(self, model, parameter):
        super().__init__(model, parameter)
        self.system_prompt_path = f"{utils.CONFIG['annotator']['system_prompt']}" 
        self.parameter_prompt_path = f"{parameter['prompt_file']}"
        output_prefix = (
            utils.CONFIG['assignment']['problem_file']
            .split('/')[1].split('.')[0]
        )
        self.output_path = utils.CONFIG['assignment']['intermediate_path']
        if not os.path.exists(self.output_path):
            os.makedirs(self.output_path)
        self.output_filename = (f"{output_prefix}_annotator_"
                                f"{model['type']}_{parameter['name']}.txt")

    def create_message_content(self):
        problem_statement = self.read_file(self.problem_path)
        program_solution = self.read_file(self.solution_path)
        output_prefix = utils.CONFIG['assignment']['problem_file'].split('/')[1].split('.')[0]  
        aggregate_feedback = self.read_file(pathlib.Path(utils.CONFIG['assignment']['intermediate_path']) /
                                            (f"{output_prefix}_aggregator_{utils.CONFIG['aggregator']['model']['type']}"
                                            f"_{self.parameter}.txt"))

        return (f"<problem> {problem_statement} </problem> \n\n"
                f"<code> {program_solution} </code> \n\n"
                f"<data> {aggregate_feedback} </data> \n\n")
