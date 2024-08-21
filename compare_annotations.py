import anthropic

import os
from pathlib import Path
import re

client = anthropic.Anthropic()

# Read the system prompt for comparator
system_prompt = ""
with open('./prompts/system_comparator.txt', 'r') as f:
    system_prompt = f.read()

dir = Path('./data/testing/C_programs_aman_arbaaz')
c_files = [f for f in os.listdir(dir) if f.endswith('.c')]
p = re.compile('([\w\d]*)\.[cC]')
output_file = Path('./data/testing/C_programs_aman_arbaaz/arbaaz_annotations/comparison_results.txt')
for file in c_files: 

    if (int(file.split('.')[0].split('_')[1]) <= 10):
        print(file)
        prefix = p.match(file).group(1)

        # Prepare the user prompt
        message_content = ""

        # Read the problem statement
        with open(Path(dir / (prefix + '.txt')), 'r') as f:
            temp = f.read()
            message_content = f"<problem>\n {temp} </problem> \n\n"

        # Read the program prefix
        with open(Path(dir / (prefix + '.c')), 'r') as f:
            temp = f.read()
            message_content += f"<student_program>\n {temp} </student_program> \n\n"

        # Read the feedback from System 1 (CodeInsight)
        with open(Path(Path('./output') / (prefix + '.c')), 'r') as f:
            temp = f.read()
            message_content += f"<system1>\n {temp} </system1> \n\n"

        # Read the feedback from System 2 (Human eval)
        with open(Path(dir / 'arbaaz_annotations' / (prefix + '.c')), 'r') as f:
            temp = f.read()
            message_content += f"<system2>\n {temp} </system2> \n\n"

        message = client.messages.create(
            model="claude-3-5-sonnet-20240620",
            max_tokens=1000,
            temperature=0,
            system=system_prompt,
            messages=[
                {
                    'role': 'user',
                    'content': [
                        {
                        'type': 'text',
                        'text': message_content
                        }
                    ]            
                }
            ] 
        )

        with open(Path(output_file), 'a') as f:
            f.write(f"File: {file}\n")
            f.write(message.content[0].text)
            f.write("\n\n")