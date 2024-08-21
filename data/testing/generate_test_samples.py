import os
import re
import pdb
import anthropic

client = anthropic.Anthropic()

with open('test_samples_prompt.txt', 'r') as f:
    user_prompt = f.read()

all_tasks = {}
p = re.compile('([\w\d]*)\.[cC]')
with open('meta_data.txt', 'r') as f:
    for line in f:
        if p.match(line):
            prog_file = p.match(line).group(1)
            f.readline()
            prog_task = f.readline()
            all_tasks[prog_file] = prog_task


for file in os.listdir('C/orig'): 

    print(file)
    prefix = p.match(file).group(1)

    with open(f'C/orig/{file}', 'r') as f:
        c_program = f.read()
        program_task = all_tasks[prefix]
        this_prompt =  user_prompt.format(C_PROGRAM_TASK = program_task, C_PROGRAM = c_program)
        response = client.messages.create(
            model = "claude-3-5-sonnet-20240620",
            max_tokens = 4000,
            temperature = 0,
            system = "You rewrite C programs to introduce intentional design flaws while maintaining their correct functionality.",
            messages = [
                {
                    "role" : "user",
                    "content" : [
                       {
                           "type" : "text",
                           "text" : this_prompt 
                       } 
                    ]
                }
            ]    
        )
    with open(f'C/noisy_sample/output_{prefix}.c', 'w') as f:
        f.write(response.content[0].text) 
        
    noisy_program = ''
    with open(f'C/noisy_sample/output_{prefix}.c', 'r') as f:
        flag = 0
        for line in f:
            if  line.startswith('<modified_program>'):
                flag = 1
                continue
            elif line.startswith('</modified_program>'):
                flag = 0
            if flag == 1:
                noisy_program += line
    
    with open(f'C/noisy_sample/{prefix}.c', 'w') as f:
        f.write(noisy_program)

    explanation = '' 
    with open(f'C/noisy_sample/output_{file}', 'r') as f:
        flag = 0
        for line in f:
            if  line.startswith('<explanation>'):
                flag = 1
                continue
            elif line.startswith('</explanation>'):
                flag = 0
            if flag == 1:
                explanation += line
    
    with open(f'C/noisy_sample/explanation_{prefix}.txt', 'w') as f:
        f.write(explanation)

    os.remove(f'C/noisy_sample/output_{prefix}.c')