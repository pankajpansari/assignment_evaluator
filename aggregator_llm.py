# Copyright (c) 2024 Pankaj Pansari 
#
# This file is part of CodeInsight, which is licensed under the MIT License.
# See the LICENSE file for details.
"""AggregatorLLM class calls given model to aggregate feedback obtained from multiple proposers.

This class is used for the second stage of the evaluation. Proposers might be incorrect at times,
or may generate conflicting feedback. The AggregatorLLM class is used to aggregate the feedback,
evaluating the proposer feedbacks for consistency and accuracy.

Typical usage example:
    
        import aggregator_llm
        aggregator = aggregator_llm.AggregatorLLM(model, parameter)
        aggregator.run()
"""
import os
import pathlib

import anthropic
import base_llm
import utils

class AggregatorLLM(base_llm.BaseLLM):
    """ Extends the BaseLLM class to implement AggregatorLLM class.

    Creates custom prompt to aggregate the feedback (proposals) obtained from 
    first stage. An individual LLM can make a mistake. The aggregation ensure
    that the feedback is consistent and accurate. The user prompt includes the
    problem statement, the program solution, name of parameter being evaluated,
    and all the proposals from the first stage. The system prompt tells exactly
    what the model is expected to do. The output is saved in an intermediate 
    log file.

    Attributes:
        system_prompt_path: A string containing the path to file describing 
            what the aggregator is expected to do.
        output_path: A string listing the directory where the aggregated result is saved.
        output_filename: A string giving the filename of result. The filename indicates
            the program name (being evaluated) and the parameter name.
    """
    def __init__(self, model, parameter):
        """ Initializes the instance based on CONFIG settings; also sets which
        LLM acts as aggregator and which parameter is being evaluated (derived 
        from parent).

        Args:
            model: A dictionary containing the model name (eg. claude-3-haiku-20240307)
                and type (eg. claude)
            parameter: A dictionary containing the parameter name and the path to
                the respective prompt file which describes the parameter.
        
        Returns:
            None
        """
        super().__init__(model, parameter)
        self.system_prompt_path = f"{utils.CONFIG['aggregator']['system_prompt']}"
        output_prefix = utils.CONFIG['assignment']['problem_file'].split('/')[-1].split('.')[0]  
        self.output_path = utils.CONFIG['assignment']['intermediate_path']
        if not os.path.exists(self.output_path):
            os.makedirs(self.output_path)
        self.output_filename = f"{output_prefix}_aggregator_{model['type']}.txt"
   
    def create_message_content(self):
        """ Creates the user prompt to be used for the aggregator LLM. The prompt
        includes the problem statement, the program solution, the name of parameter 
        being evaluated, followed by a list of all proposals from the first stage.
        
        Args:
            None

        Returns:
            str: A string containing the user prompt for the aggregator LLM.
        """
        problem_statement = self.read_file(self.problem_path)
        program_solution = self.read_file(self.program_path)

        proposals = []
        output_prefix = utils.CONFIG['assignment']['problem_file'].split('/')[-1].split('.')[0]  
        for model in utils.CONFIG['proposers']['models']:
            proposals.append(self.read_file(pathlib.Path(self.output_path) / 
                                            f"{output_prefix}_proposer_{model['type']}"
                                            f"_{self.parameter}.txt"))

        proposal_prompt = ''
        for i, proposal in enumerate(proposals):
            proposal_prompt += f"<data> {proposal} </data>\n\n"

        return (f"<problem> {problem_statement} \n\n"
                f"<instruction> Parameter to assess : {self.parameter} " # no parameter prompt; parameter name is enough
                f"</problem> \n\n"  
                f"<code> {program_solution} </code> \n\n"
                f"<proposals> {proposal_prompt} </proposals>")
    
    def write_output(self, response, output_filename):
        """ Append the output to a file.

        Args:
            response: An object of type Messages or ChatCompletion containing 
            the response from the model.
            output_filename: A string containing the name of the output file.
            The filename remains the same for all parameters.

        Returns:
            None
        """
        output_file = pathlib.Path(self.output_path) / output_filename 
        if isinstance(self.get_client(), anthropic.Anthropic):
            content = response.content[0].text
        else:
            content = response.choices[0].message.content

        os.makedirs(output_file.parent, exist_ok=True)
        with open(output_file, 'a', encoding = 'utf-8') as f:
            f.write(f"{self.model['name']}\n")
            f.write(f"{self.parameter}\n")
            f.write(content)
            f.write("\n\n")

