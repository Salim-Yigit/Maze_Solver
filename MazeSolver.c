#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include <windows.h>

struct Stack {
    int top;
    unsigned capacity;
    int* array;
};


void FileRead(char *file_name,int matris[70][70],int *n,int *m);
void printMatris(int matris[70][70],int n,int m); 
void Initilaze(int matris[70][70],int *n,int *m,int visited[70][70]); 
struct Stack* createStack(unsigned capacity);
int findExit(int matris[70][70],int visited[70][70],int i,int j,int *puan,struct Stack *stack,char maze[70][70],int n,int m);
void ReunionMaze(int matris[70][70],int n,int m,char maze[70][70]);
void printMaze(char maze[70][70],int n,int m,int x,int y,int kontol);

int main() { 

	int matris[70][70];  
	int n,m,puan;
	puan=0;
	char maze[70][70];
	int visited[70][70];
	srand(time(NULL)); 
	FileRead("maze.txt",matris,&n,&m); 
	Initilaze(matris,&n,&m,visited); 
	//printMatris(matris,n,m);
	struct Stack *stack=createStack(300);
	//printMatris(visited,&n,&m);
	int i=n-2,j=1; 
	ReunionMaze(matris,n,m,maze);
	//printMaze(maze,n,m,3,3);
	//printMaze(maze,n,m,i,2);
	//printf("%d %d\n",n,m);
	//printMaze(matris,n,m,i,j);
	//printMaze(matris,&n,&m);
	//printMatris(visited,&n,&m);
	findExit(matris,visited,i,j,&puan,stack,maze,n,m); 
	return 0;
}  

void printMatris(int matris[70][70],int n,int m) { 
	int i,j;
	printf("\n");
	for(i=0;i<n;i++) { 
		for(j=0;j<m;j++) { 
			//if(matris[i][j]!='\0') 
				printf("%d ",matris[i][j]);
		} 
		printf("\n");
	}
}
void FileRead(char *file_name,int matris[70][70],int *n,int *m) { 
	FILE *fp=fopen(file_name,"r");
	int row=0,column=0,max_col=0; 
	char c;
	if(fp==NULL) 
		printf("File can not open"); 
	
	while(( c= fgetc(fp))!=EOF) {  
		c= (char) c;
		//printf("%c",c);
		if(c!='\n') { 
			if(c!=' ') { 
				matris[row][column]=0; 
				column++;
				if(max_col<column) 
					max_col=column;
			}else { 
				matris[row][column]=1; 
				column++; 
				if(max_col<column) 
					max_col=column;
			} 	
		}else { 
			row++;
			column=0;
		}
	} 
	row--;
	max_col--;
	*n=row;
	*m=max_col;	 
	//printf("m file read sonu:%d\n",*m);
} 
void Initilaze(int matris[70][70],int *n,int *m,int visited[70][70]) {
	// Bu fonksiyon çýkýþ ve giriþ noktalarýný matrise yerleþtirir.Ayrýca rastgele elma koyar. 
	srand(time(NULL));
	int elma_sayisi=20; 
	int bas_row=*n-2,bit_col=*m-2; 
	int row,col,i,j;
	//printf("bas_row:%d\n",bas_row); 
	//printf("bit_col:%d\n",bit_col); 
	matris[bas_row][1]=3; // baþlangýç noktasý
	matris[bas_row][bit_col]=4; // bitiþ noktasý
	while(elma_sayisi>0) {
		row=rand()%*n;
		col=rand()%*m;
		if(matris[row][col]==1) {
			matris[row][col]=5; // orada elma var.Elma olan noktalrý da matriste belirtmek için 5'e atadým.
			elma_sayisi--;
		}	
	} 
	for(i=0;i<*n;i++) { 
		for(j=0;j<*m;j++) { 
			visited[i][j]=0;
		}
	} 
	visited[i-2][1]=1;
}  


struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}
 

int isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}
 

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}
 

void push(struct Stack* stack, int item) {
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}
 

int pop(struct Stack* stack) {
    if (isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top--];
}
 

int peek(struct Stack* stack) {
    if (isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top];
} 

void ReunionMaze(int matris[70][70],int n,int m,char maze[70][70]) { 
	int i,j;
	for(i=0;i<n;i++) { 
		for(j=0;j<m;j++) {
			if(matris[i][j]==0 && i%2==0 && j%2==0) { 
				maze[i][j]='+';
			}else if(matris[i][j]==1){ 
				maze[i][j]=' ';
			}else if(matris[i][j]==3) { 
				maze[i][j]='b';
			}else if(matris[i][j]==4) { 
				maze[i][j]='c';
			}else if(matris[i][j]==0 && i%2==1){ 
				maze[i][j]='|';
			}else if(matris[i][j]==0 && i%2==0 && j%2==1) {
				maze[i][j]='-';
			}else if(matris[i][j]==5){ 
				maze[i][j]='O';
			}
		}
	} 
	maze[n-2][1]='*';/*
	for(i=0;i<n;i++) { 
		for(j=0;j<m;j++) {
			printf("%c",maze[i][j]);
		} 
		printf("\n");
	} 
	printf("\n");*/
}
void printMaze(char maze[70][70],int n,int m,int x,int y,int kontrol) {  
	int i,j;
	printf("\n"); 
	if(kontrol==1)
		maze[x][y]='*'; 
	else 
		maze[x][y]=' ';
	for(i=0;i<n;i++) { 
		for(j=0;j<m;j++) { 
			printf("%c",maze[i][j]);
		} 
		printf("\n");
	}
}

int findExit(int matris[70][70],int visited[70][70],int i,int j,int *puan,struct Stack *stack,char maze[70][70],int n,int m) {  
	printf("\n puaniniz:%d\n",*puan); 
	printMaze(maze,n,m,i,j,1);
	usleep(300000);
	if(matris[i+1][j]==1 && visited[i+1][j]==0) {  	
		push(stack,1); 
		//printf("Asagi gitti\n");
		visited[i+1][j]=1;
		return findExit(matris,visited,i+1,j,puan,stack,maze,n,m);
	}else if(matris[i+1][j]==5 && visited[i+1][j]==0) { 
		*puan=*puan+10;  
		//printf("Asagi gitti elma buldu.\n");
		push(stack,1);
		visited[i+1][j]=1; 
		return findExit(matris,visited,i+1,j,puan,stack,maze,n,m);
	}else if(matris[i-1][j]==1 && visited[i-1][j]==0) {  
		//printf("Yukari gitti.\n");
		visited[i-1][j]=1; 
		push(stack,2);
		return findExit(matris,visited,i-1,j,puan,stack,maze,n,m);
	}else if(matris[i-1][j]==5 && visited[i-1][j]==0) { 
		*puan=*puan+10;  
		//printf("Yukari gitti.Elma buldu\n");
		push(stack,2);
		visited[i-1][j]=1; 
		return findExit(matris,visited,i-1,j,puan,stack,maze,n,m);  
	}else if(matris[i][j+1]==1 && visited[i][j+1]==0) {  
		//printf("Saga gitti.\n");
		visited[i][j+1]=1; 
		push(stack,3);
		return findExit(matris,visited,i,j+1,puan,stack,maze,n,m);
	}else if(matris[i][j+1]==5 && visited[i][j+1]==0) {  
		//printf("Saga gitti,elam buldu.\n");
		*puan=*puan+10;   
		visited[i][j+1]=1;  
		push(stack,3);
		return findExit(matris,visited,i,j+1,puan,stack,maze,n,m);  
	}else if(matris[i][j-1]==1 && visited[i][j-1]==0) { 
		//printf("Sola gitti.\n");
		visited[i][j-1]=1;  
		push(stack,4);
		return findExit(matris,visited,i,j-1,puan,stack,maze,n,m);  
	}else if(matris[i][j-1]==5 && visited[i][j-1]==0) {   
		//printf("Sola gitti.Elma buldu\n");
		*puan=*puan+10;  
		visited[i][j-1]=1;  
		push(stack,4);
		return findExit(matris,visited,i,j-1,puan,stack,maze,n,m);  
	}else if(matris[i+1][j]==4) { 
		visited[i+1][j]=1; 
		printf("\n"); 
		printMaze(maze,n,m,i+1,j,1);
		printf("puaniniz:%d\n",*puan);
		printf("Cikisa ulastiniz."); 
		return 0;
	}else if(matris[i-1][j]==4) {  
		visited[i-1][j]=1;  
		printf("\n"); 
		printMaze(maze,n,m,i-1,j,1);
		printf("puaniniz:%d\n",*puan); 
		printf("Cikisa ulastiniz."); 
		return 0;
	}else if(matris[i][j+1]==4) {  
		visited[i][j+1]=1; 
		printf("\n"); 
		printMaze(maze,n,m,i,j+1,1); 
		printf("puaniniz:%d\n",*puan); 
		printf("Cikisa ulastiniz."); 
		return 0;
	}else if(matris[i][j-1]==4) {  
		visited[i][j-1]=1; 
		printf("\n");
		printMaze(maze,n,m,i,j-1,1); 
		printf("puaniniz:%d\n",*puan); 
		printf("Cikisa ulastiniz."); 
		return 0;
	}else { 	
		int k=0; 
		if(matris[i+1][j]==0) { 
			k++;
		} 
		if(matris[i][j+1]==0) { 
			k++;
		} 
		if(matris[i-1][j]==0) { 
			k++;
		} 
		if(matris[i][j-1]==0) { 
			k++;
		} 
		if(k>=3) { 
			*puan=*puan-5; 
		}
 		if(peek(stack)==1) {  
			pop(stack); 
			printMaze(maze,n,m,i,j,2);
			return 	findExit(matris,visited,i-1,j,puan,stack,maze,n,m);
		}else if(peek(stack)==2) {
			pop(stack);   
				printMaze(maze,n,m,i,j,2);
			return 	findExit(matris,visited,i+1,j,puan,stack,maze,n,m);
		}else if(peek(stack)==3) {  
			pop(stack);   
				printMaze(maze,n,m,i,j,2);
			return 	findExit(matris,visited,i,j-1,puan,stack,maze,n,m);
		}else if(peek(stack)==4) { 
			pop(stack);    
				printMaze(maze,n,m,i,j,2);
			return 	findExit(matris,visited,i,j+1,puan,stack,maze,n,m);
		}
	}
}  

