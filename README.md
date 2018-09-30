# Search For Threats

This application is intended too be a static code analysis tool to aid in code
reviews. The goal is to detect places where vulnerabilities such as
injection, XSS, directory traversal, etc. occur. Another goal is to be language
agnostic so that this tool can be utilized for reviewing applications from any
language.

## Note

This tool is simply scanning files for regular expression matches. It is not
following code paths to determine if user proceeds without any sanitization.
This tool does not try to be smart but rather to identify the areas of the
codebase where manual review may be beneficial.

## Features To Implement

- Show context in match output
- Report to CSV
- Ignore file
- Vulnerability type search
- Interactive mode
  - Mark as ignore
    - Store hash of line and un-ignore when line changes
  - Mark as issue
  - Add note
