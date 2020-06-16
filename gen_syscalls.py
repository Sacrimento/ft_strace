import requests
from lxml import html
import re

page = requests.get('http://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/')
content = html.fromstring(page.content).xpath('//table/tr/td/text()')

indeces = list(i for i,val in enumerate(content) if val.isnumeric())
syscalls = [content[v+1:indeces[i+1]] for i,v in enumerate(indeces) if i+1 < len(indeces)]

with open('./syscall', 'w') as f:
    out = ''
    for syscall in syscalls:
        for i,arg in enumerate(syscall[1:]):
            if 'unsigned int' in arg:
                syscall[1+i] = 'UINT'
            elif 'int' in arg:
                syscall[1+i] = 'INT'
            elif 'unsigned long' in arg or 'size_t' in arg:
                syscall[1+i] = 'ULONG'
            elif 'long' in arg:
                syscall[1+i] = 'LONG'
            elif 'filename' in arg:
                syscall[1+i] = 'FILENAME'
            elif 'char *' in arg and '[]' in arg:
                syscall[1+i] = 'STRING_ARRAY'
            elif 'char *' in arg:
                syscall[1+i] = 'STRING'
            else:
                syscall[1+i] = 'ADDR'
            
        out += '{"%s", %d, {%s}, LONG},\n' % (syscall[0][4:], len(syscall[1:]), ', '.join(syscall[1:]))
    f.write(out)
