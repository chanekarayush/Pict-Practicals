# Assignment Writer Skill

## What does this skill do?

It automatically writes a complete university assignment for you — formatted as a Word document (`.docx`) — using your lab manual as the source.

You just tell Claude which assignment you want written and provide the lab manual PDF. Claude reads the manual, extracts the relevant content, expands on the theory using its own knowledge, and produces a ready-to-submit `.docx` file in the standard university assignment format.

---

## What you get

A Word document with all the standard sections filled in:

- **Assignment No.** — with blank fields for Roll Number, Date of Performance, and Date of Submission
- **Problem Definition** — exactly as you provide it
- **Learning Objective** — 2 concise points on what the experiment aims to teach
- **Learning Outcome** — 2 points on what you will have learned after completing it
- **Concepts Related to Theory** — the main content section; topic-wise bullet points expanded with relevant knowledge, plus diagrams where applicable
- **Algorithm** — step-by-step (only included if the assignment involves an actual algorithm or code)
- **Test Cases** — a table for code/algorithm assignments, or scenario descriptions for software/tool-based ones
- **Conclusion** — 1–2 sentences stating what was accomplished

---

## What you need to provide

| Input | Description |
|-------|-------------|
| **Lab manual PDF** | Upload the PDF for the relevant assignment |
| **Assignment number** | e.g., `Assignment 3` or `BI III` |
| **Problem definition** | The exact problem statement for this assignment (usually given by your teacher or printed in the manual) |

That's it — Claude figures out everything else from the manual.

---

## Example prompt

> Here is my BI lab manual. Write Assignment 4.
> Problem Definition: To study and implement data visualization using Power BI.

---

## Notes

- The document is A4-sized with standard 1-inch margins, suitable for Indian university submissions.
- Theory diagrams from the manual (e.g., architecture diagrams, data flow diagrams) are recreated as ASCII art inside the document. Software screenshots are not included.
- The Algorithm section is skipped automatically for tool-based assignments (e.g., Power BI, Excel, SQL setup).
