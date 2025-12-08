# Final-Project-478

CECS 478, Sec01, Samuel Addington, Fall 2025, Tiffany Nguyen, Giselle Hernandez

Format String Guardian: Lightweight static scanner and a 26-case regression suite

References:
https://hackinglab.cz/en/blog/format-string-vulnerability/
https://www.usenix.org/legacy/events/sec01/full_papers/cowanbarringer/cowanbarringer.pdf
https://cecs478-lecture-app-pywv5.ondigitalocean.app/exploitation.html
https://owasp.org/www-community/attacks/Format_string_attack

Problem Statement:
Detecting unsafe format-string usage in code is a common security issue that often goes overlooked. Unsafe format strings like using, printf(user_input) can cause crashes, strange outputs, and even security issues in lower-level languages. These bugs are often small mistakes, but they can be hard to notice in code review. To help with this, we want to make a small Format-String Guardian tool that uses an lightweight static scanner and flags risky patterns. We’ll also build a 25-case regression suit to test the tool.

Success Metrics
For the Format-String Guardian the detection accuracy should have a high unsafe case detection rate and a low false positive rate (a specific number cannot be estimated at this time). The performance speed should be very quick. The checker should print clear messages like “Integrity failed at Line 7” and be easily legible. These metrics aren’t fully designed, but give a rough estimate and measure to show in the final report.
