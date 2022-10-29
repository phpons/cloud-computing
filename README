# Before everything, some of my notes:
## Previous level of experience:
I had some previous experience with Docker and Kubernetes before this class, but not much at all with Asm and this kind of low level work.

## Frequency of commits
The commits in this repository are concentrated in two/three different weeks. 

This was not intentional; I had been working on this assignment during all weeks since it was quite complicated for me, but my code was not clean enough for me to "accept" publishing it. I even helped out classmates who were having trouble progressing in the first week assignment.

In the end, I procrastinated pushing the clean version of my answers and code, so I hope it is understandable that I was not slacking around over the other weeks. 

This should also be noticeable from how quick the progress of these commits are, since I'm simply transferring "dirty" work to a clean repo. I do part-time research on top of the university courses, so it was much easier for me to properly clean out a repository on the weekend.

This section is referring to this:
>Nota Bene: if we see nothing in the git log for a week, 
we will assume that you did not work that week.

---------------------------------------------------
Overview (from the original file)
---------------------------------------------------

This directory is where you will do your work, it 
is composed of:

  - documents
  - workspace
  
The directory "documents" contains a couple of 
interesting readme files and a course of how 
to use GDB if you are new to debugging with gdb.
In the coming weeks, you will given other documents,
mostly PDF ones, that you may add to this folder
for documents.

The directory "workspace" is very important, it is 
the place where you will do your actual work.

You will start by creating a local git repository
for the content of directory "workspace" and do the
first initial commit with the provided file ".gitignore".
Edit the file ".gitignore" as you see fit, it is tailored
to C development and the use of the Eclipse IDE. It is compatible
also with the use of VSCode.

  $ cd workspace
  $ git init
  $ git add .gitignore
  $ git commit -m "Initial commit"
   
The branch "master" will be the official release 
of your work, with tags for each step of your homework.
Never do actual work in your master, never break.

In the directory "workspace/worklog", you will maintain
a worklog of everything you do, in the classroom and at 
home. You will use text-only formats, such pure text files 
or markdown, so that git can manage diffs correctly.

Overall, the work will be organized as steps. You will 
git-tag the completion of each step. There must be work 
done in this repository, weekly, and there must be 
git-commits that correspond.  

---------------------------------------------------
Git Repository
---------------------------------------------------

The directory "workspace" is a git repository, therefore
be sure to avoid putting large non-textual documents 
there, such as pdf or large images, or worse, videos.
The idea is to keep your git repository small.

First, the git repository will help you try out stuff,
using branches that you can toss if the experiment fails.
Working at a low-level like bare metal development is 
delicate and it is easy to break everything. A rigorous
use of GIT branches is the way to go.

The core principle: always work in a branch that you can 
throw away or at least in a way that you can throw away
the changes since the last commit. This is the easiest
approach to organize your work when working with git.

NEVER break your master branch. Never do work on the master
branch. When about to merge a branch "B" in the branch "master",
always merge the branch "master" in your working branch "B"
before merging the branch "B" in the branch "master".

Second, we will use the git to see what you did and when
you did it. It is mandatory that you commit each time you 
work and tag your work for each step. 

Nota Bene: if we see nothing in the git log for a week, 
           we will assume that you did not work that week.

---------------------------------------------------
WorkLog
---------------------------------------------------

We ask that you maintain a work log, as one or more files under
the directory "workspace/worklog", files where you will keep 
track of everything you do, the questions you have, and the answers
you find. 

You will use text-only formats, such pure text files or markdown, 
so that git can manage diffs correctly. If you generate non-textual
documents, make sure to add the proper lines in the file .gitignore.

Important, it is not the usual report for the teaching staff, 
it is a worklog for yourself, helping track of what you learn. 
So the contents must be helpful for you and will be dependent 
on the skills and experience you already have, but it cannot be 
empty. An empty worklog would mean that you did not work.

---------------------------------------------------
arm.boot
---------------------------------------------------

This is a makefile project, with the initial sources
given to you as a starting point for your bare-metal
software development.
