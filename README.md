# DSFinalProject

My <i>Data Structures and Algorithmes</i> course final project.

## Project
<p>
  The main idea of project was to create a calculator that can evaulate operations on big numbers, like 50 digit numbers.<br />
  This calculator also has a cursor which lets you to manage the string before evaulation.<br />
</p>

### Basic ideas
<p>
  For evaulation we use the post-fix format which we need to build from an in-fix string.<br />
  Since calculating big numbers needs a large memory space, we decrease our results by moding them by <b>10^9 + 7</b>.<br />
  Also we use a hash-map to store the results, thus in case of evaulation old strings, we just get them from our cache.<br />
</p>
