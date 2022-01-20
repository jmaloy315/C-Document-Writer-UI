/*Jack Maloy, 116329200, jmaloy*/
#include "document.h"
#include <stdio.h>
#include <string.h>

/*init_document initializes a documement doc, which is named
name. The document has 0 paragraphs upon initialization.*/
int init_document(Document *doc, const char *name){
  if(doc==NULL || name==NULL || strlen(name) > MAX_STR_SIZE){
    return FAILURE;
  }else{
  doc->number_of_paragraphs = 0;
  strcpy(doc->name, name);
  
  return SUCCESS;
  }
}

/*reset_document takes in a document doc, 
and sets the number of paragraphs to 0.*/
int reset_document(Document *doc){
  if(doc==NULL){
    return FAILURE;
  }else{
    doc->number_of_paragraphs = 0;
    return SUCCESS;
  }
}

/*print_document prints all of the contents of a document doc.*/
int print_document(Document *doc){
  if(doc!=NULL){
    int i, j;
    printf("Document name: \"%s\"\n", doc->name);
    printf("Number of Paragraphs: %d\n", doc->number_of_paragraphs);

    for(i=0; i<doc->number_of_paragraphs; i++){
      for(j=0; j<doc->paragraphs[i].number_of_lines; j++){
	printf("%s\n", doc->paragraphs[i].lines[j]);
      }
      if(i<(doc->number_of_paragraphs - 1)){
	printf("\n");
      }
    }
    return SUCCESS;
  }
  return FAILURE;
}

/*add_paragraph_after adds a paragraphs to doc, after the paragraph
number paragraph_number.*/
int add_paragraph_after(Document *doc, int paragraph_number){
 int i; 
	   
 if(doc==NULL || doc->number_of_paragraphs==MAX_PARAGRAPHS ||  
    paragraph_number>MAX_PARAGRAPHS || paragraph_number<0){ 
   return FAILURE; 
 }else{ 
   if(paragraph_number == 0 && !(doc->number_of_paragraphs)){ 
     doc->paragraphs[0].number_of_lines = 0; 
   } 
   if(paragraph_number == doc->number_of_paragraphs){ 
     doc->paragraphs[doc->number_of_paragraphs].number_of_lines = 0; 
   }else{ 
     for(i=doc->number_of_paragraphs; i>=paragraph_number; i--){ 
       doc->paragraphs[i+1] = doc->paragraphs[i]; 
     } 
     doc->paragraphs[paragraph_number].number_of_lines = 0; 
   } 
   (doc->number_of_paragraphs)++; 
   return SUCCESS; 
 } 
}

/*add_line_after adds a line new_line to the document doc, in the paragraph
paragraph_number, at line number line_number.*/
int add_line_after(Document *doc, int paragraph_number, int line_number,
		   const char *new_line){
  int i, number_of_lines;
  if(doc!=NULL && new_line != NULL){
    if(paragraph_number <= doc->number_of_paragraphs){
      number_of_lines = doc->paragraphs[paragraph_number-1].number_of_lines;
      if(number_of_lines<MAX_PARAGRAPH_LINES && line_number <= number_of_lines){
	
	if(line_number==0){
	  strcpy(doc->paragraphs[paragraph_number-1].lines[0], new_line);
	}
	if(line_number==number_of_lines){
	  strcpy(doc->paragraphs[paragraph_number-1].lines[line_number],
		 new_line);
	}else{
	  for(i=line_number; i<number_of_lines; i++){ 
	      strcpy(doc->paragraphs[paragraph_number-1].lines[i+1],
		     doc->paragraphs[paragraph_number-1].lines[i]);
	  }
	  strcpy(doc->paragraphs[paragraph_number-1].lines[line_number],
		 new_line);
	}
	(doc->paragraphs[paragraph_number-1].number_of_lines)++;
	return SUCCESS;
      }
    }
  }
  return FAILURE;
}

/*get_number_lines_paragraph returns the number of lines in a paragraph*/
int get_number_lines_paragraph(Document *doc, int paragraph_number, 
			       int *number_of_lines){
  int count;
  
  if(doc==NULL || number_of_lines==NULL || 
     paragraph_number<=doc->number_of_paragraphs){
    return FAILURE;
  }else{
    
    count = doc->paragraphs[paragraph_number].number_of_lines;
    *number_of_lines = count;
    
    return SUCCESS;
  }
}

/*append_line appends a line new_line onto the paragraph paragraph_number.*/
int append_line(Document *doc, int paragraph_number, 
		const char *new_line){
  int number_of_lines;/*number_of_lines is used to make code more readable.*/
  if(doc!=NULL && new_line != NULL){
    number_of_lines = doc->paragraphs[paragraph_number-1].number_of_lines;
    if(paragraph_number <= doc->number_of_paragraphs && 
       number_of_lines<MAX_PARAGRAPH_LINES){
      
      add_line_after(doc, paragraph_number, number_of_lines, new_line);
	
      return SUCCESS;
    }
 }
 return FAILURE;
}

/*remove_line removes a line from doc, which is located in paragraph
paragraph_number at the line line_number.*/
int remove_line(Document *doc, int paragraph_number, int line_number){

  int i, number_of_lines;
 
  if(doc!=NULL){
    number_of_lines = doc->paragraphs[paragraph_number-1].number_of_lines;
    if(paragraph_number <= doc->number_of_paragraphs){
      if(number_of_lines<MAX_PARAGRAPH_LINES && line_number <= number_of_lines){
	if(line_number==number_of_lines){
	  (doc->paragraphs[paragraph_number-1].number_of_lines)--;
	  return SUCCESS;
	}
	for(i=line_number-1; i<number_of_lines-1; i++){
	  
	  strcpy(doc->paragraphs[paragraph_number-1].lines[i],
		 doc->paragraphs[paragraph_number-1].lines[i+1]);
	}
	(doc->paragraphs[paragraph_number-1].number_of_lines)--;
	return SUCCESS;
      }
    }
  }
  return FAILURE;
}

/*load_document takes a string data and loads it into the document doc. An
empty string "" signifies that a new paragraph is to be added.*/
int load_document(Document *doc, char data[][MAX_STR_SIZE + 1], 
		  int data_lines){
  int i, added = 1;/*added is used to signify where a paragraph should be
		     added upon multile calls of load_document.*/
  
  if(doc==NULL || data==NULL || data_lines==0){
    return FAILURE;
  }else{
    add_paragraph_after(doc, 0);
    for(i=0; i<data_lines; i++){
      if(strcmp(data[i],"")==0){
	add_paragraph_after(doc, added);
	added++;
      }else{
	append_line(doc, added, data[i]);
      }
    }
    return SUCCESS;
  }
}

/*replace_text searches through doc, finds all instances of the substring 
  target, and replaces it with the string replacement.*/
int replace_text(Document *doc, const char *target, 
		 const char *replacement){
  int i,j;
  char temp[MAX_STR_SIZE + 1] = {0};
  char *marker;
  if(doc==NULL || target==NULL || replacement==NULL){
    return FAILURE;
  }else{
    for(i=0; i<doc->number_of_paragraphs; i++){
      for(j=0; j<doc->paragraphs[i].number_of_lines; j++){
	marker = strstr(doc->paragraphs[i].lines[j], target);
        while(marker != '\0'){
	  strcpy(temp, marker);
	  strcpy(marker, "");
	  strcat(marker, replacement);
	  strcat(marker+strlen(replacement), temp+strlen(target));
	  marker = strstr(marker + strlen(target), target);
	}
      }
    }
    return SUCCESS;
  }
}

/*highlight_text finds the substring target in the document doc, and surrounds
it with the symbolic constants HIGHLIGHT_START_STR and HIGHLIGHT_END_STR, 
which highlights that substring.*/
int highlight_text(Document *doc, const char *target){
  char temp[MAX_STR_SIZE+1] = "";
  
  if(doc==NULL || temp==NULL){
    return FAILURE;
  }else{
    strcpy(temp, HIGHLIGHT_START_STR);
    strcat(temp, target);
    strcat(temp, HIGHLIGHT_END_STR);
    replace_text(doc, target, temp);
    return SUCCESS;
  }
}

/*remove_text searches through all of the document doc and removes all
instances of the substring target.*/
int remove_text(Document *doc, const char *target){
  if(doc==NULL || target==NULL){
    return FAILURE;
  }else{
    replace_text(doc, target, "");
    return SUCCESS;
  }
}

/*load_file acts similar to load_document, except it reads fron a file.*/
int load_file(Document *doc, const char *filename){
  char line[MAX_STR_SIZE + 1], first, temp[MAX_STR_SIZE+1];
  FILE *stream;
  int check, index=1;
  size_t length;
  
  if(doc==NULL && filename==NULL){
    return FAILURE;
  }else{
    if((stream=fopen(filename, "r"))==NULL){
      return FAILURE;
    }else{
      add_paragraph_after(doc, 0);
      while(fgets(line, MAX_STR_SIZE + 1, stream)){
	length = strlen(line)-1;
	check = sscanf(line, "%c%s", &first, temp);
	if(line[length]=='\n'){
	  line[length] = '\0';
	}
	if(check > 1){
	  append_line(doc, index, line);
	}else{
	  add_paragraph_after(doc, index);
	  index++;
	}
      }
      return SUCCESS;
    }
  }
}

/*Save document saves the contents of a doc onto a new file
named after filename. */
int save_document(Document *doc, const char *filename){
  FILE *ret;
  int i, j;
  
  if(doc==NULL || filename==NULL){
    return FAILURE;
  }else{
     if((ret=fopen(filename, "w"))==NULL){
      return FAILURE;
     }else{
       for(i=0; i<doc->number_of_paragraphs; i++){
	 for(j=0; j<doc->paragraphs[i].number_of_lines; j++){
	   fputs(doc->paragraphs[i].lines[j], ret);
	   if(j<doc->paragraphs[i].number_of_lines){
	     fputs("\n", ret);
	   }
	 }
	 if((i+1) < doc->number_of_paragraphs){
	   fputs("\n", ret);
	 }
       }
       fclose(ret);
       return SUCCESS;
     }
  }
  return FAILURE;
}
