## Automatic Grading of Lab Programming Assignments using Llama-3 LLM

The code here has been written with a view to assist our TAs in grading lab programming assignments for the Fundamentals of Computer Systems undergraduate course at Plaksha university. These assignments are in C. There are two axes along which a submission is graded: functionality and quality of code. We use an agent-based approach using state-of-the-art large language models (LLMs) to accurate, consistently, and reliably provide feedback about the quality of the submission.

### **Functionality**
The functionality of the code is going to be tested on a comprehensive set of test-cases. The output of the submission is compared with the expected output for each test case. This part is relatively easy to automate by writing appropriate autotester, though coming up with a good test suite is challenging. The test suite should ensure a mix of sanity checks, comprehensive coverage, robustness checks and stress tests. We defer the use of LLMs to generate good test suite for the time being.

### **Quality of Code**

The first component of feedback of the quality of code comes from a clean compile and clean run under valgrind. It is easy to automate for these quality metrics. The second and most important component of quality feedback is the TA's commentary from the code review. It is this component that we seek to automate using LLMs. The parameters for grading are as follows:

1. Reasonable efficiency: Though the runtime and memory usage of a program can be gauged using benchmark tests, we can a different approach to save effort. We seek to use the judgement of LLMs to decide when the submission is grossly inefficient in its implementation. We note that this is in addition to the hard timeout constraints in functionality testing. 

2. Cleanliness/readability

3. Language conventions

4. Program design

5. Data structures

6. Pointers/memory

Each of these parameters are scored on a scale of 0-10. Adding in the grade out of 10 for clean compile and valgrind run (5 + 5), we take an average of these scores. For the code review, we also return the code marked up with comments generated from LLM feedback. This individualized feedback on the code quality will highlight opportunities for future improvement and commend the students' successes.

### Technical Details

The success of automated grading of code quality hinges on these factors:

1. Quality and detail of rubrics for each of the parameters: We need to be precise and detailed about what we are looking for in each of the parameters.

2. Quality of the LLMs: Due to the complexity of the assignments, we need to make use of the best LLMs we can. This necessitates the use of LLMs with largest parameter counts available to us. We choose to use a mix of Llama 3.1 405B Instruct Turbo, GPT-4o, Mixtral-8x22B Instruct (141B), and Claude 3.5 Sonnet.

3. Mixture of Agents approach: We aggregrate the responses from multiple LLMs to get a more robust and reliable feedback. The multiple feedbacks help us estimate uncertainty; this enables manual intervention in cases where the feedback is conflicting. We also make use of a code completion LLM to insert comments in the original code at appropriate places.