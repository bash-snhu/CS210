# Creator Information  
> Brooklen Ashleigh  
> **Creation Date:** October, 2022  
> **Class:** CS210  

## Summarize the project and what problem it was solving.

This project creates a simple user interface that allows a Grocery Store to analyze their daily sales. The user can:
  1. View a list of all items purchase that day, along with how many times the item was purchased
  1. Search for a single item to see how many times it was purchased
  1. Print a histogram of item sales that day

## What did you do particularly well?

I tried to organize my code to eliminate as much repeat processing as possible. The code reads the list of daily sales, finds frequencies, and creates the .dat file when the program is started, so this process is completed once. After that, the .dat file is analyzed as needed. I commented most parts of the code so that it is clear what each part does.

## Where could you enhance your code? How would these improvements make your code more efficient, secure, and so on?

- I believe I could make my code even more efficient by returning the frequency list and keeping it in memory somehow so that the .dat file wouldn't have to be read so many times. However, I'm not sure which way is more efficient.
- I could figure out how to safely rename my project files so that they match and make more sense.
- I need to figure out placement of necessary Python files so that someone could pull and run this project easily

## Which pieces of the code did you find most challenging to write, and how did you overcome this? What tools or resources are you adding to your support network?

The most challenging part was figuring out how to do input validation for cin and fstream. I figured out the common issues with both of these by googling and reading solutions on stack overflow.

## What skills from this project will be particularly transferable to other projects or course work?

Learning how to combine C++ and Python into a single project will definitely help with later projects and coursework, I imagine.

## How did you make this program maintainable, readable, and adaptable?

I tried to comment as much as necessary and organize functions, etc. in a way that is easily readable. I used naming conventions that I hope make sense. One thing I could definitely improve on is figuring out what files are necessary to make a C++ project downloadable and readable straight from Github. I'm sure as it stands now someone would not be able to run this project without some setup.
