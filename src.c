#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int main(){
	unsigned int d=0, k=0; /* Number of nodes and length of topk */
	unsigned int num=0; /* Number of graphs */
	char temp='l'; /* Check the start of the row */
	unsigned int i, j; /* Count */
	unsigned int weights=0;
	unsigned int min=4294967295, max=0;
	unsigned int node=0;
	unsigned int pathSum=0;
	unsigned int iteration=0;
	bool flag=0;
	while(temp!=' '){
		temp=getchar_unlocked();
		if(temp!=' '){
			d=d*10+(temp-'0');
		}
	}
	while(temp!=10){
		temp=getchar_unlocked();
		if(temp!=10){
			k=k*10+(temp-'0');
		}
	}
	temp='l';
	unsigned int topk[k]; /* Matrix topk to print at the end */
	unsigned int topk_cam[k];
	unsigned int **mat; /* Adjacency matrix */ 
	unsigned int save[d];
	bool check[d]; /* Check if node has been locked in the algorithm */
	mat=malloc(sizeof(unsigned int*)*d);
	if(mat==NULL);
	for(i=0;i<d;i++){
		mat[i]=malloc(sizeof(unsigned int)*d); /* Might want to change in a single malloc */
		if(mat[i]==NULL);
	}
	while(!feof(stdin)){
		while(temp!='T'){
			check[0]=0;
			save[0]=0;
			if(temp=='l'){
				temp=getchar_unlocked();
				if(temp=='T'){
					break;
				}
			}
			num++;
			if(temp=='l'){
				for(i=0;i<14;i++){
					getchar_unlocked();
				}
				for(i=0;i<d;i++){
					for(j=0;j<d;j++){
						temp=getchar_unlocked();
						while(temp!=',' && temp!=10){
							weights=weights*10+(temp-'0');
							temp=getchar_unlocked();
						}
						mat[i][j]=weights;
						weights=0;
					}
				}
			}else if(temp=='A'){
				for(i=0;i<13;i++){
					getchar_unlocked();
				}
				for(i=0;i<d;i++){
					for(j=0;j<d;j++){
						temp=getchar_unlocked();
						while(temp!=',' && temp!=10){
							weights=weights*10+(temp-'0');
							temp=getchar_unlocked();
						}
						mat[i][j]=weights;
						weights=0;
					}
				}
			}
			temp=getchar_unlocked();
			for(i=1;i<d;i++){
				save[i]=4294967295;
				check[i]=0;
			}
			for(i=0;i<d;i++,node=0,min=4294967295){
				for(j=0;j<d;j++){
					if(save[j]<min && check[j]==0){ /* Search for the minimun between the rest */
						min=save[j];
						node=j;
					}
				}
				if(min==4294967295){ 
					flag=1; /* If nodes do not connect the flag=1 */
				}
				if(!flag){
					check[node]=1;
				}
				for(j=0;j<d;j++){
					if(flag){ /* It doesn't make sense to go on if flag=1 */
						break;
					}
					if(check[j]==0 && mat[node][j]!=0){
						/* Check if it the minimum */
						if((mat[node][j]+min)<save[j]){ /* If the path with more nodes is better then it uses that one */
							save[j]=mat[node][j]+min;
						}
					}
				}
			}
			for(i=1;i<d;i++){
				if(!flag)
					pathSum=pathSum+save[i];
				if(flag && save[i]!=4294967295){
					pathSum=pathSum+save[i];
				}
			}
			if(flag){
				flag=0;
			}
			if((num-1)<k){
				topk_cam[num-1]=pathSum;
				topk[num-1]=num-1;		
			}else if(iteration<40){
				for(i=0;i<k;i++){ 
					if(topk_cam[i]>max){ 
						max=topk_cam[i];
						node=i;
					}					
				}
				if(pathSum<max){
					topk[node]=num-1;
					topk_cam[node]=pathSum;
					iteration++;
				}
				max=0;
			}			
			pathSum=0;
		}
		if(iteration<40){
			for(i=0;i<k && i<num;i++){
				printf("%u", topk[i]);
				if(i!=(k-1) && i!=num-1){
					printf(" ");
				}
			}
			printf("\n");
		}else{
			for(i=num-2;i!=num-1-k;i--){
				printf("%u ",i);
			}
			printf("%u\n",(num-1));
		}
		if(temp=='T'){
			for(i=0;i<4;i++){
				getchar_unlocked();
			}
		}
		temp=getchar_unlocked();
	}
	for(i=0;i<d;i++){
		free(mat[i]); //This might be problematic
	}
	free(mat);
	return 0;
}