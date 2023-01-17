#ifndef __json_util_h
#define __json_util_h
#include<stdlib.h>
#include<string.h>
#include <stdarg.h>

#define INDENT 4
#define SAFE_SPACE 8

char* j_item(char* key, char* value);
char* j_group(char* key, char** value, int n, char* group_type);
char* indent(char* str, int indent_length);
char** make_group(int num,...);

/*
 * json item
*/
char* j_item(char* key, char* value)
{
    char *str = (char *)malloc(sizeof(char)*(strlen(key)+strlen(value)+SAFE_SPACE));
    char *ptr = str;
    unsigned int index = 0;

    if(strcmp(key,"")!=0)
    {
        // insert key
        *ptr = '\"';
        ptr++;
        for(index = 0; index<strlen(key); index++)
        {
            *ptr = key[index];
            ptr++;
        }
        *ptr = '\"';
        ptr++;

        *ptr = ':';
        ptr++;
        *ptr = ' ';
        ptr++;
    }
    
    // insert value
    *ptr = '\"';
    ptr++;
    for(index = 0; index<strlen(value); index++)
    {
        *ptr = value[index];
        ptr++;
    }
    *ptr = '\"';
    ptr++;

    *ptr = '\0';

    return str;
}

/*
 * json object or array based on group type
 *
 * group type can be either "{}" or "[]"
 * 
 * value is an array of string items
*/
char* j_group(char* key, char** value, int n, char* group_type)
{
    unsigned int value_length = 0;
    unsigned int row = 0;
    
    for(row = 0; row < n; row++)
    {
        value_length += strlen(value[row]);
    }

    char *str = (char *)malloc(sizeof(char)*(strlen(key) + (INDENT*value_length*SAFE_SPACE)));
    char *ptr = str;
    unsigned int index = 0;

    if(strcmp(key,"")!=0)
    {
        // insert key
        *ptr = '\"';
        ptr++;
        for(index = 0; index<strlen(key); index++)
        {
            *ptr = key[index];
            ptr++;
        }
        *ptr = '\"';
        ptr++;

        *ptr = ':';
        ptr++;
        *ptr = ' ';
        ptr++;
    }
    
    *ptr = group_type[0];
    ptr++;

    for(row = 0; row < n; row++)
    {
        // indentation
        *ptr = '\n';
        ptr++;
        
        char* indent_str = indent(value[row], INDENT);

        for(index = 0; index < strlen(indent_str); index++)
        {
            // insert value (j_item)
            for(index = 0; index<strlen(indent_str); index++)
            {
                *ptr = indent_str[index];
                ptr++;
            }
        }

        if(row < n-1)
        {
            *ptr = ',';
            ptr++;
        }
    }

    *ptr = '\n';
    ptr++;
    // closing bracket
    *ptr = group_type[1];
    ptr++;

    // end of string
    *ptr = '\0';

    return str;
}

/**
 * Indents a string by adding spaces as per indent_length.
 * 
 */
char* indent(char* str, int indent_length)
{
    unsigned int count = 0, i = 0, j = 0, c = 0;
    // count new lines
    for(i = 0; str[i] != '\0'; i++)
    {
        if(str[i] == '\n')
        {
            count++;
        }
    }
    char *buf = (char *)malloc(sizeof(char)*(strlen(str) + (count*(indent_length+1)) + SAFE_SPACE));
    for(i = 0; str[i] != '\0'; i++)
    {
        if(i == 0)
        {
            c = 0;
            while(c < indent_length)
            {
                buf[j] = ' ';
                j++;
                c++;
            }
            buf[j] = str[i];
            j++;
        }
        else if (str[i] == '\n')
        {
            buf[j] = str[i];
            j++;
            c = 0;
            while(c < indent_length)
            {
                buf[j] = ' ';
                j++;
                c++;
            }
        }
        else
        {
            buf[j] = str[i];
            j++;
        }
    }
    return buf;
}

/**
 * makes list of strings of num number of elements
 * the elements can be either of type j_item or j_group (char*)
 */
char** make_group(int num,...) {
    va_list valist;
    va_start(valist, num);
    unsigned int i=0;

    char **items = (char **)malloc(sizeof(char*)*num);
    for (i = 0; i < num; i++) {
        items[i] = va_arg(valist, char*);
    }
   /* clean memory reserved for valist */
   va_end(valist);
   return items;
}

#endif
