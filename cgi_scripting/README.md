# CGI scripting in C
This is supposed to be a set of small programs to handle http requests and provides dynamic content,
much like how a php script would do, but i wrote those in c.
## How it works
C CGI scripts receive inputs like (query strings, URLs, POST fields) in environment variables passed to the
c program by the http server, the program uses the <stdlib.h> getenv() to access those inputs.
the programs should then output the proper content type header like:
```
content-type: text/plain
```
to stdout, usually using printf(), maybe with some other optional headers and then the main content sent to the 
client browser (usually HTML or JSON).

## How to get them working
1. compile source files into a.cgi object files, for example:
    gcc showvars.c -o showvars.cgi
2. put the object files in the http server specified cgi-bin directory, for me (using apache) it's:
    /srv/http/cgi-bin
3. set the proper permissions (the files must be executable by others).
4. write an html page invoking the script like this one for example:
```html
<Html>
<Body>
<A Href="/cgi-bin/evars.cgi?Testing_Testing_1_2_3">See the environment vars!</a> 
</Body>
</Html>
```
