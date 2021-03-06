//
//  main.c
//  Assigenmenr1_CRC
//
//  Created by Bowen Li on 2017/10/9.
//  Copyright © 2017年 Bowen Li. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include<string.h>

#define MAXNUM 80000
struct bits_8 bit_output;
struct frame frame_output;

struct bits_8 {
    char string;
    int data[8];
}bits_out;

struct frame{
    int no;
    int vaild_num;
    int start;
    int end;
    int size_b;
    struct bits_8   orignal_bits[64];
    struct bits_8   final_bits[64];
    struct bits_8   convert_final_bits[64];
    int data [MAXNUM];
    int bool_valid;
    int size;
    int is_b;
}frame_out;


int compare(int *a, int * b){
    int flag = 0;
    for (int i = 0; i < 17; i++)
    {
        if (a[i] != b[i])
        {
            flag = 1;
            return 0;
        }
    }
    return 1;
}

void char_binary(char a, int* array) {
    int i = 0;
    int b=(int) a;
    if(b<0){
        b=b+256;
    }
    for (i = 0; i < 8; i++) {
        array[7 - i] = b % 2;
        b /= 2;
    }
}




/*int  frame_valid(struct frame *temp){
    
    
    for(int i=0;i<temp->vaild_num;i++){
        for(int m=0; m<8;m++){
            temp->convert_final_bits[i].data[m] =temp->final_bits[i].data[m];
        }
    }
    
    
    
    for(int i=0;i<temp->vaild_num-2;i++){
        int temp_convert[8];
        for(int m=0; m<8;m++){
            temp_convert[m]=temp->final_bits[i].data[m];
        }
        temp->convert_final_bits[i].data[0]=temp_convert[0];
        temp->convert_final_bits[i].data[1]=temp_convert[4];
        temp->convert_final_bits[i].data[2]=temp_convert[1];
        temp->convert_final_bits[i].data[3]=temp_convert[5];
        temp->convert_final_bits[i].data[4]=temp_convert[2];
        temp->convert_final_bits[i].data[5]=temp_convert[6];
        temp->convert_final_bits[i].data[6]=temp_convert[3];
        temp->convert_final_bits[i].data[7]=temp_convert[7];
    }
    for(int i=0;i<temp->vaild_num;i++){
        for(int m=0;m<8;m++){
            temp->data[i*8+m]=temp->convert_final_bits[i].data[m];
        }
    }
    if(temp->vaild_num==0){
        temp->bool_valid=0;
    }
    else{
        int len_frame=temp->vaild_num*8;
        int generator[17]={1,0,1,1,0,0,0,0,1,0,0,0,1,0,0,1,1};
        int array[17];
        for(int i=0;i<17;i++){
            array[i]=temp->data[i];
        }
        int idx=16;
        while(idx!=len_frame-1){
            if(array[0]==0){
                for(int i=0;i<17;i++){
                    array[i] = array[i+1];
                }
                idx++;
                array[16] =temp->data[idx];
            }
            else{
                for (int i = 0; i < 17; i++) {
                    if (array[i] == generator[i])
                        array[i] = 0;
                    else
                        array[i] = 1;
                }
                
            }
        }
        
        for(int i=0;i<17;i++){
            //printf("%d",array[i]);
        }
        // printf("\n");
        
        char com1[17]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        char com2[17]={1,0,1,1,0,0,0,0,1,0,0,0,1,0,0,1,1};
        if(strcmp(array,com1)==0||strcmp(array,com2)==0){
            temp->bool_valid=1;
            
        }
        else temp->bool_valid=0;
        0,1,1,0,0,0,0,1,0,1,0,1,0,1,1,1,0,0,0,1,1,1,0,0,1,0,1,1,0,0,0,1,0,1,1,0,0,0,0,1
        
        
    }
    //printf("\n");
    
    return 0;
}*/
int  frame_valid(struct frame *temp){
    
    for(int i=0;i<temp->size;i++){
      
        for(int m=0; m<8;m++){
            
            temp->final_bits[i].data[m] =temp->orignal_bits[i].data[m];
            //printf("%d",temp->final_bits[i].data[m]);
        }
    }
    //printf("\n");
    for(int i=1;i<temp->size-1;i++){
        
        for(int m=0; m<8;m++){
            
            //temp->final_bits[i].data[m] =temp->orignal_bits[i].data[m];
            //printf("%d",temp->final_bits[i].data[m]);
        }
    }
    //printf("\n");
    
    for(int i=1;i<=temp->size-4;i++){
        int temp_convert[8];
        for(int m=0; m<8;m++){
            temp_convert[m]=temp->orignal_bits[i].data[m];
        }
        temp->final_bits[i].data[0]=temp_convert[0];
        temp->final_bits[i].data[1]=temp_convert[4];
        temp->final_bits[i].data[2]=temp_convert[1];
        temp->final_bits[i].data[3]=temp_convert[5];
        temp->final_bits[i].data[4]=temp_convert[2];
        temp->final_bits[i].data[5]=temp_convert[6];
        temp->final_bits[i].data[6]=temp_convert[3];
        temp->final_bits[i].data[7]=temp_convert[7];
    }
    for(int i=1;i<=temp->size-2;i++){
        for(int m=0;m<8;m++){
            //printf("%d",temp->final_bits[i].data[m]);
            temp->data[(i-1)*8+m]=temp->final_bits[i].data[m];
        }
    }
    //printf("\n");
    for(int i=0;i<(temp->size-2)*8;i++){
    //printf("%d",temp->data[i]);
    }
    //printf("\n");
    
    if(temp->size==0){
        temp->bool_valid=0;
    }
    else{
        int len_frame=(temp->size-2)*8;
        int generator[17]={1,0,1,1,0,0,0,0,1,0,0,0,1,0,0,1,1};
        int array[17];
        for(int i=0;i<17;i++){
            array[i]=temp->data[i];
        }
        int idx=16;
        while(idx!=len_frame-1){
            if(array[0]==0){
                for(int i=0;i<17;i++){
                    array[i] = array[i+1];
                }
                idx++;
                array[16] =temp->data[idx];
            }
            else{
                for (int i = 0; i < 17; i++) {
                    if (array[i] == generator[i])
                        array[i] = 0;
                    else
                        array[i] = 1;
                }
                
            }
        }
        for(int i=0;i<17;i++){
            //printf("%d",array[i]);
        }
        //printf("\n");
        int com1[17]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        int com2[17]={1,0,1,1,0,0,0,0,1,0,0,0,1,0,0,1,1};
        if(compare(array, com1)==1||compare(array, com2)==1){
            if(temp->bool_valid!=2)
            temp->bool_valid=1;
            
        }
        else temp->bool_valid=0;
        
        
        
    }
    //printf("\n");
    
    return 0;
}




/*int convert_frame_final(struct frame *temp){
    int valid_bits_num=0;
    for(int i=1; i<temp->size-1;i++){
        
        if(temp->orignal_bits[i].string=='b'){
            if(temp->orignal_bits[valid_bits_num+1].string!='b'||temp->orignal_bits[valid_bits_num+1].string!='a'){
                temp->bool_valid=0;
            }
            else {
                temp->final_bits[valid_bits_num]=temp->orignal_bits[i+1];
                valid_bits_num++;
                i++;
            }
        }
        
        if(temp->orignal_bits[i].string!='b'){
            valid_bits_num++;
            temp->final_bits[valid_bits_num-1]=temp->orignal_bits[i];
        }
    }
    temp->vaild_num=valid_bits_num;
    frame_valid(temp);
    //printf("%d\n",temp.bool_valid);
    return 0;
}*/


/*int creat_frame(struct bits_8 *temp){
    if(frame_output.start==0){
        if(temp->string=='a'){
            frame_output.start=1;
            frame_output.orignal_bits[frame_output.size]=*temp;
            frame_output.size++;
            return 0;
        }
    }
    
    if(frame_output.start==1){
        if(temp->string=='a'&& frame_output.orignal_bits[frame_output.size-1].string!='b'){
            frame_output.orignal_bits[frame_output.size]=*temp;
            frame_output.size = frame_output.size+1;
            frame_output.start=0;
            frame_output.no++;
            //printf("Frame %d   Size: %d\n",frame_output.no-1,frame_output.size);
            convert_frame_final(&frame_output);
            if(frame_output.bool_valid==1){
                //printf("Frame %d  Valid Size: %d\n",frame_output.no-1,frame_output.size);
                for(int i=1;i<frame_output.vaild_num-2;i++){
                    //printf("%c",frame_output.final_bits[i].string);
                }
            }
            else
                // printf("Frame %d  Invalid\n",frame_output.no-1);
                //printf("%d\n",frame_output.bool_valid);
                if(frame_output.bool_valid==1){
                    
                }
            frame_output.size=0;
            return 0;
        }
        else{
            frame_output.orignal_bits[frame_output.size]=*temp;
            frame_output.size = frame_output.size+1;
            return 0;
        }
    }
    
    return 0;
}*/
int creat_frame(struct bits_8 *temp,struct frame *fram_output){
    if ((temp->string=='b')&&fram_output->is_b==0){
        fram_output->is_b=1;
        fram_output->size_b++;
        return 0;
    }
    else if (temp->string=='b'&&fram_output->is_b==1){
        fram_output->is_b=0;
        fram_output->orignal_bits[fram_output->size]=*temp;
        fram_output->size++;
        return 0;
    }
    else if(temp->string=='a'&&fram_output->is_b==1){
        fram_output->is_b=0;
        fram_output->orignal_bits[fram_output->size]=*temp;
        fram_output->size++;
        return 0;
    }
    else if(temp->string=='a'&&fram_output->is_b==0) {
        if(fram_output->start==0){
            fram_output->start=1;
            fram_output->orignal_bits[fram_output->size]=*temp;
            fram_output->size++;
            return 0;
        }
        if(fram_output->start==1){
            fram_output->end=1;
            fram_output->orignal_bits[fram_output->size]=*temp;
            fram_output->size++;
            return 0;
        }
        
    }
    else if(temp->string!='a'&&temp->string!='b'&&fram_output->is_b==1){
        fram_output->is_b=0;
        fram_output->bool_valid=2;
        fram_output->orignal_bits[fram_output->size]=*temp;
        fram_output->size++;
        return 0;
    }
    else{
        fram_output->is_b=0;
        fram_output->orignal_bits[fram_output->size]=*temp;
        fram_output->size++;
        return 0;
    }
    
    return 0;
}





int main() {
    int binary_array[8];
    int fram_num=0;
    FILE *fp = fopen("output", "rb");
    FILE *fp2=fopen("text.txt","w");
    if( fp == NULL)
        printf("Error at opening files!\n");
    /****************/
    frame_output.start=0;
    //frame_output.size=0;
    frame_output.no=0;
    frame_output.bool_valid=0;
    frame_output.is_b=0;
    /****************/
    fseek(fp,0,SEEK_SET);
    while(feof(fp)!=1){
        /**************************/
        fread(&bit_output.string,1,1,fp);
        char_binary(bit_output.string,binary_array);
        for (int tm = 0; tm < 8; tm++) {
            bit_output.data[tm]=binary_array[tm];
        }
        /***************************/
        creat_frame(&bit_output,&frame_output);
        if(frame_output.start==1&&frame_output.end==1){
           
            
            frame_valid(&frame_output);
           
            if(frame_output.bool_valid==1){
                if (fram_num==2){
                    for(int i=0;i< frame_output.size;i++){
                        //printf("%c",frame_output.orignal_bits[i].string);
                        for(int m=0;m<8;m++){
                            //printf("%d",frame_output.orignal_bits[i].data[m]);
                        }
                    }
                }
                //printf("frame %d,  Size %d：Valid\n",fram_num,frame_output.size+frame_output.size_b);
                for(int i=1; i<=frame_output.size-4;i++){
                    printf("%c", frame_output.orignal_bits[i].string);
                    fputc(frame_output.orignal_bits[i].string,fp2);
                }
            }
            else {
                /*if (fram_num==2){
                    for(int i=0;i< frame_output.size;i++){
                       // printf("%c",frame_output.orignal_bits[i].string);
                        for(int m=0;m<8;m++){
                    //printf("%d",frame_output.orignal_bits[i].data[m]);
                        }
                    }
                }*/
                //printf("\n");
                //printf("%d\n",fram_num);
                //printf("frame %d,  Size %d：Invalid\n",fram_num,frame_output.size+frame_output.size_b);
               
            }
            fram_num++;
            frame_output.size=0;
            frame_output.start=0;
            frame_output.end=0;
            frame_output.size_b=0;
            frame_output.bool_valid=0;
        }
        
        //printf("%d\n",frame_output.bool_valid);
        
    }
    //printf("\n");
    fclose(fp);
    return 0;
}

