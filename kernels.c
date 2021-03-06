/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/* 
 * Please fill in the following student struct 
 */
student_t student = {
    "Nathan A Lile",     /* First member full name */
    "lilen@colorado.edu"  /* First member email address */
};

/***************
 * ROTATE KERNEL
 ***************/
/*
 * naive_rotate - The naive baseline version of rotate 
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst) 
{
    int i, j;
    for (i = 0; i < dim; i+=2){
        for (j = 0; j < dim; j+=2){
            dst[RIDX(dim-1-j, i, dim)].red   = src[RIDX(i, j, dim)].red;
            dst[RIDX(dim-1-j, i, dim)].green = src[RIDX(i, j, dim)].green;
            dst[RIDX(dim-1-j, i, dim)].blue  = src[RIDX(i, j, dim)].blue;
            dst[RIDX(dim-1-j-1, i, dim)].red   = src[RIDX(i, j+1, dim)].red;
            dst[RIDX(dim-1-j-1, i, dim)].green = src[RIDX(i, j+1, dim)].green;
            dst[RIDX(dim-1-j-1, i, dim)].blue  = src[RIDX(i, j+1, dim)].blue;

            dst[RIDX(dim-1-j, i+1, dim)].red   = src[RIDX(i+1, j, dim)].red;
            dst[RIDX(dim-1-j, i+1, dim)].green = src[RIDX(i+1, j, dim)].green;
            dst[RIDX(dim-1-j, i+1, dim)].blue  = src[RIDX(i+1, j, dim)].blue;
            dst[RIDX(dim-1-j-1, i+1, dim)].red   = src[RIDX(i+1, j+1, dim)].red;
            dst[RIDX(dim-1-j-1, i+1, dim)].green = src[RIDX(i+1, j+1, dim)].green;
            dst[RIDX(dim-1-j-1, i+1, dim)].blue  = src[RIDX(i+1, j+1, dim)].blue;
        
        }
    }
}

/*
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/

char attempt_1_rotate_descr[] = "Attempt 1===working with loop unrolling";
void attempt_1_rotate(int dim, pixel *src, pixel *dst) 
{
    
  int block_1 = 16;
  int block_2 = 16;   
 int i, j, i1, j1;
  for(i1 = 0; i1 < dim; i1 += block_1) {
    for(j1 = 0; j1< dim; j1 += block_2){
      for (i = i1; i < i1+block_1; i+=2){
        for (j = j1; j < j1+block_2; j+=2){
            dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
            dst[RIDX(dim-1-j-1, i, dim)]   = src[RIDX(i, j+1, dim)];
            ///////////////////////// taking care of i+1 ////////////////////////////////////////
            dst[RIDX(dim-1-j, i+1, dim)]  = src[RIDX(i+1, j, dim)];
            dst[RIDX(dim-1-j-1, i+1, dim)]   = src[RIDX(i+1, j+1, dim)];
            
        
        }
      }
    }
  }
}

#define work(x) dst[RIDX(dim-1-j, i+(x), dim)] = src[RIDX(i+(x), j, dim)];
char attempt_2_rotate_descr[] = "Attempt 2===========function call inside loop with static incrimenting of inner variables";
void attempt_2_rotate(int dim, pixel *src, pixel *dst) 
{
   int i, j;

    for (i = 0; i < dim; i += 16) 
        for (j = 0; j < dim; j++) {
            work(0);work(1);work(2);work(3);
            work(4);work(5);work(6);work(7);
            work(8);work(9);work(10);work(11);
            work(12);work(13);work(14);work(15);

        }
}
/*
NOTES:
we do the work of the inner for loop in an external function and call in the loop. Function calls are faster then iteration work
dst = dim^2-dim+dst
*dst = *src
src = src+dim
*(dst+1) = (*src)
*/
char attempt_3_rotate_descr[] = "Attempt 3===========using pointers for src and dst";
void attempt_3_rotate(int dim, pixel *src, pixel *dst) 
{
   int i, j, dim_local;
   pixel *src_ptr, *dst_ptr;
   dim_local = dim;
  
    for (i = 0; i < dim_local; i += 32){ 
        for (j = 0; j <dim; j++) {
        dst_ptr = dst+RIDX(dim-1-j, i, dim_local);
        src_ptr = src+RIDX(i,j, dim_local);  
        *(dst_ptr) = *(src_ptr);
        src_ptr+=dim_local;
        *(dst_ptr+1) = *(src_ptr);
        src_ptr+=dim_local;
        *(dst_ptr+2) = *(src_ptr);
        src_ptr+=dim_local;
        *(dst_ptr+3) = *(src_ptr);
        src_ptr+=dim_local;
        *(dst_ptr+4) = *(src_ptr);
        src_ptr+=dim_local;
        *(dst_ptr+5) = *(src_ptr);
        src_ptr+=dim_local;
        *(dst_ptr+6) = *(src_ptr);
        src_ptr+=dim_local;
        *(dst_ptr+7) = *(src_ptr);
        src_ptr+=dim_local;
        *(dst_ptr+8) = *(src_ptr);
        src_ptr+=dim_local;
        *(dst_ptr+9) = *(src_ptr);
        src_ptr+=dim_local;
        *(dst_ptr+10) = *(src_ptr);
        src_ptr+=dim_local;
        *(dst_ptr+11) = *(src_ptr);
        src_ptr+=dim_local;
        *(dst_ptr+12) = *(src_ptr);
        src_ptr+=dim_local;
        *(dst_ptr+13) = *(src_ptr);
        src_ptr+=dim_local;
        *(dst_ptr+14) = *(src_ptr);
        src_ptr+=dim_local;
        *(dst_ptr+15) = *(src_ptr);
        src_ptr+=dim_local;
        *(dst_ptr+16) = *(src_ptr);
        src_ptr+=dim_local;
        *(dst_ptr+17) = *(src_ptr);
        src_ptr+=dim_local;
        *(dst_ptr+18) = *(src_ptr);
        src_ptr+=dim_local;
        *(dst_ptr+19) = *(src_ptr);
        src_ptr+=dim_local;
        *(dst_ptr+20) = *(src_ptr);
        src_ptr+=dim_local;
        *(dst_ptr+21) = *(src_ptr);
        src_ptr+=dim_local;
        *(dst_ptr+22) = *(src_ptr);
        src_ptr+=dim_local;
        *(dst_ptr+23) = *(src_ptr);
        src_ptr+=dim_local;
        *(dst_ptr+24) = *(src_ptr);
        src_ptr+=dim_local;
        *(dst_ptr+25) = *(src_ptr);
        src_ptr+=dim_local;
        *(dst_ptr+26) = *(src_ptr);
        src_ptr+=dim_local;
        *(dst_ptr+27) = *(src_ptr);
        src_ptr+=dim_local;
        *(dst_ptr+28) = *(src_ptr);
        src_ptr+=dim_local;
        *(dst_ptr+29) = *(src_ptr);
        src_ptr+=dim_local;
        *(dst_ptr+30) = *(src_ptr);
        src_ptr+=dim_local;
        *(dst_ptr+31) = *(src_ptr);
        }
   }
}
/*
NOTES:
32 fold-loop unrolling and pointers for src and dst
swaped i and j to get a slight bump in speed
let inner loop decriment rather then incriment for slight increase in speed
TRY LOCAL DIM VARIABLE
*/

/*
char attempt_4_rotate_descr[] = "Attempt 4===========loop blocking and loop unrolling using pointers to src and dst";
void attempt_4_rotate(int dim, pixel *src, pixel *dst) 
{
    //Block size to tune
  int block_1 = 8;
  int block_2 = 8;
  int i,j,i1,j1, dim_local;
pixel *src_ptr, *dst_ptr;
  dim_local = dim_squared_ish;
  for(i1 = 0; i1 < dim_local; i1 += block_1) {
    for(j1 = 0; j1< dim_local; j1 += block_2) {
            for(i = i1; i < i1 + block_1; i+=8){
                for(j = j1; j < j1 + block_2; j++){
                            dst_ptr = dst+RIDX(dim-1-j, i, dim_local);
                            src_ptr = src+RIDX(i,j, dim_local);  
                            *(dst_ptr) = *(src_ptr);
                            src_ptr+=dim_local;
                            *(dst_ptr+1) = *(src_ptr);
                            src_ptr+=dim_local;
                            *(dst_ptr+2) = *(src_ptr);
                            src_ptr+=dim_local;
                            *(dst_ptr+3) = *(src_ptr);
                            src_ptr+=dim_local;
                            *(dst_ptr+4) = *(src_ptr);
                            src_ptr+=dim_local;
                            *(dst_ptr+5) = *(src_ptr);
                            src_ptr+=dim_local;
                            *(dst_ptr+6) = *(src_ptr);
                            src_ptr+=dim_local;
                            *(dst_ptr+7) = *(src_ptr);
/* 
                             src_ptr+=dim_local;
                            *(dst_ptr+8) = *(src_ptr);
                             src_ptr+=dim_local;
                            *(dst_ptr+9) = *(src_ptr);
                            src_ptr+=dim_local;
                            *(dst_ptr+10) = *(src_ptr);
                            src_ptr+=dim_local;
                            *(dst_ptr+11) = *(src_ptr);
                            src_ptr+=dim_local;
                            *(dst_ptr+12) = *(src_ptr);
                            src_ptr+=dim_local;
                            *(dst_ptr+13) = *(src_ptr);
                            src_ptr+=dim_local;
                            *(dst_ptr+14) = *(src_ptr);
                            src_ptr+=dim_local;
                            *(dst_ptr+15) = *(src_ptr);
                            src_ptr+=dim_local;
                            *(dst_ptr+16) = *(src_ptr);
                            src_ptr+=dim_local;
                            *(dst_ptr+17) = *(src_ptr);
                            src_ptr+=dim_local;
                            *(dst_ptr+18) = *(src_ptr);
                            src_ptr+=dim_local;
                            *(dst_ptr+19) = *(src_ptr);
                            src_ptr+=dim_local;
                            *(dst_ptr+20) = *(src_ptr);
                            src_ptr+=dim_local;
                            *(dst_ptr+21) = *(src_ptr);
                            src_ptr+=dim_local;
                            *(dst_ptr+22) = *(src_ptr);
                             src_ptr+=dim_local;
                            *(dst_ptr+23) = *(src_ptr);
                            src_ptr+=dim_local;
                            *(dst_ptr+24) = *(src_ptr);
                            src_ptr+=dim_local;
                            *(dst_ptr+25) = *(src_ptr);
                            src_ptr+=dim_local;
                            *(dst_ptr+26) = *(src_ptr);
                            src_ptr+=dim_local;
                            *(dst_ptr+27) = *(src_ptr);
                            src_ptr+=dim_local;
                            *(dst_ptr+28) = *(src_ptr);
                            src_ptr+=dim_local;
                            *(dst_ptr+29) = *(src_ptr);
                            src_ptr+=dim_local;
                            *(dst_ptr+30) = *(src_ptr);
                            src_ptr+=dim_local;
                            *(dst_ptr+31) = *(src_ptr);
                            
                }
            }
        }
    }

}
*/
/*
NOTES:
You should think of I[RIDX(i,j,n)] as equivalent to I[i][j].
Accessing the array in A[i][j] order, taking advantage of spatial locality why so slow?
*/
char attempt_5_rotate_descr[] = "Attempt 5===========using pointers for src and dst, loop unrolling on i and some  other tweeking";
void attempt_5_rotate(int dim, pixel *src, pixel *dst) 
{
   int i, j, dim_local, dim_squared_ish;
  dim_local = dim;
  dim_squared_ish = (dim-1)*dim;
  dst+=dim_squared_ish;
    for (i = 0; i < dim_local; i += 32){ 
        for (j = 0; j <dim; j++) { 
//1        
        *dst = *src;
        src+=dim_local;
        dst+=1;
//2
        *dst = *src;
        src+=dim_local;
        dst+=1;
//3
        *dst = *src;
        src+=dim_local;
        dst+=1;
//4
        *dst = *src;
        src+=dim_local;
        dst+=1;
//5  
        *dst = *src;
        src+=dim_local;
        dst+=1;
//6
        *dst = *src;
        src+=dim_local;
        dst+=1;
//7
        *dst = *src;
        src+=dim_local;
        dst+=1;
//8
        *dst = *src;
        src+=dim_local;
        dst+=1;
//9
        *dst = *src;
        src+=dim_local;
        dst+=1;
//10
        *dst = *src;
        src+=dim_local;
        dst+=1;
//11
        *dst = *src;
        src+=dim_local;
        dst+=1;
//12
        *dst = *src;
        src+=dim_local;
        dst+=1;
//13
        *dst = *src;
        src+=dim_local;
        dst+=1;
//14
        *dst = *src;
        src+=dim_local;
        dst+=1;
//15
        *dst = *src;
        src+=dim_local;
        dst+=1;
//16
        *dst = *src;
        src+=dim_local;
        dst+=1;
//17
        *dst = *src;
        src+=dim_local;
        dst+=1;
//18
        *dst = *src;
        src+=dim_local;
        dst+=1;
//19
        *dst = *src;
        src+=dim_local;
        dst+=1;
//20
        *dst = *src;
        src+=dim_local;
        dst+=1;
//21
        *dst = *src;
        src+=dim_local;
        dst+=1;
//22
        *dst = *src;
        src+=dim_local;
        dst+=1;
//23
        *dst = *src;
        src+=dim_local;
        dst+=1;
//24
        *dst = *src;
        src+=dim_local;
        dst+=1;
//25
        *dst = *src;
        src+=dim_local;
        dst+=1;
//26
        *dst = *src;
        src+=dim_local;
        dst+=1;
//27
        *dst = *src;
        src+=dim_local;
        dst+=1;
//28
        *dst = *src;
        src+=dim_local;
        dst+=1;
//29
        *dst = *src;
        src+=dim_local;
        dst+=1;
//30
        *dst = *src;
        src+=dim_local;
        dst+=1;
//31
        *dst = *src;
        src+=dim_local;
        dst+=1;

//32
        *dst = *src;

        src++;
        src -= (dim<<5)-dim;
        dst-=31+dim;
                }
            dst+=dim_squared_ish +dim;
            dst+=32;
            src += 31*dim;
        
   }
}
char playGround_rotate_descr[] = "PLAYGROUND======optimize array index cacheing";
void playGround_rotate(int dim, pixel *src, pixel *dst) 
{	
    //You should think of I[RIDX(i,j,n)] as equivalent to I[i][j]
int i, j, j_1;
		int size = 32;
		for(i = 0; i < dim; i+=size)
			for(j = 0; j < dim; j+=size)
				for(j_1 = j; j_1 < j+size; j_1++) {
					dst[RIDX(dim-1-j_1, i+0, dim)] = src[RIDX(i+0, j_1, dim)];
					dst[RIDX(dim-1-j_1, i+1, dim)] = src[RIDX(i+1, j_1, dim)];
					dst[RIDX(dim-1-j_1, i+2, dim)] = src[RIDX(i+2, j_1, dim)];
					dst[RIDX(dim-1-j_1, i+3, dim)] = src[RIDX(i+3, j_1, dim)];
					dst[RIDX(dim-1-j_1, i+4, dim)] = src[RIDX(i+4, j_1, dim)];
					dst[RIDX(dim-1-j_1, i+5, dim)] = src[RIDX(i+5, j_1, dim)];
					dst[RIDX(dim-1-j_1, i+6, dim)] = src[RIDX(i+6, j_1, dim)];
					dst[RIDX(dim-1-j_1, i+7, dim)] = src[RIDX(i+7, j_1, dim)];
					dst[RIDX(dim-1-j_1, i+8, dim)] = src[RIDX(i+8, j_1, dim)];
					dst[RIDX(dim-1-j_1, i+9, dim)] = src[RIDX(i+9, j_1, dim)];
					dst[RIDX(dim-1-j_1, i+10, dim)] = src[RIDX(i+10, j_1, dim)];
					dst[RIDX(dim-1-j_1, i+11, dim)] = src[RIDX(i+11, j_1, dim)];
					dst[RIDX(dim-1-j_1, i+12, dim)] = src[RIDX(i+12, j_1, dim)];
					dst[RIDX(dim-1-j_1, i+13, dim)] = src[RIDX(i+13, j_1, dim)];
					dst[RIDX(dim-1-j_1, i+14, dim)] = src[RIDX(i+14, j_1, dim)];
					dst[RIDX(dim-1-j_1, i+15, dim)] = src[RIDX(i+15, j_1, dim)];
					dst[RIDX(dim-1-j_1, i+16, dim)] = src[RIDX(i+16, j_1, dim)];
					dst[RIDX(dim-1-j_1, i+17, dim)] = src[RIDX(i+17, j_1, dim)];
					dst[RIDX(dim-1-j_1, i+18, dim)] = src[RIDX(i+18, j_1, dim)];
					dst[RIDX(dim-1-j_1, i+19, dim)] = src[RIDX(i+19, j_1, dim)];
					dst[RIDX(dim-1-j_1, i+20, dim)] = src[RIDX(i+20, j_1, dim)];
					dst[RIDX(dim-1-j_1, i+21, dim)] = src[RIDX(i+21, j_1, dim)];
					dst[RIDX(dim-1-j_1, i+22, dim)] = src[RIDX(i+22, j_1, dim)];
					dst[RIDX(dim-1-j_1, i+23, dim)] = src[RIDX(i+23, j_1, dim)];
					dst[RIDX(dim-1-j_1, i+24, dim)] = src[RIDX(i+24, j_1, dim)];
					dst[RIDX(dim-1-j_1, i+25, dim)] = src[RIDX(i+25, j_1, dim)];
					dst[RIDX(dim-1-j_1, i+26, dim)] = src[RIDX(i+26, j_1, dim)];
					dst[RIDX(dim-1-j_1, i+27, dim)] = src[RIDX(i+27, j_1, dim)];
					dst[RIDX(dim-1-j_1, i+28, dim)] = src[RIDX(i+28, j_1, dim)];
					dst[RIDX(dim-1-j_1, i+29, dim)] = src[RIDX(i+29, j_1, dim)];
					dst[RIDX(dim-1-j_1, i+30, dim)] = src[RIDX(i+30, j_1, dim)];
					dst[RIDX(dim-1-j_1, i+31, dim)] = src[RIDX(i+31, j_1, dim)];
				}
}

/*

====NOTES=======
STEPS
1) optimize for loops

   - performing loop unrolling for the inner loop, rather then doing an 32 factor unrollilng.
   - sets static variable for the dimension of the unrolliing so it is not recalcualted over and over size = 32;
   - reduced the dst[RIDX(dim-1-j1, i+0, dim)] = src[RIDX(i+0, j1, dim)].red, green and blue to single statement.
   - 3rd for loop to decriment the j variable by the same amount the i variable is being incrimented by
        i) this allows for more efficitne caching of the array index iinformation in memory??
not 100% sure why this works so damn well, ask CA's
*/
char rotate_descr[] = "rotate: Current working version";
void rotate(int dim, pixel *src, pixel *dst) 
{
    playGround_rotate(dim, src, dst);
    attempt_1_rotate(dim, src, dst);
    attempt_2_rotate(dim, src, dst);
    attempt_3_rotate(dim, src, dst);
    //attempt_4_rotate(dim, src, dst);
    attempt_5_rotate(dim, src, dst);
}

/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_rotate_functions() 
{
    add_rotate_function(&naive_rotate, naive_rotate_descr);   
    add_rotate_function(&rotate, rotate_descr);   
    add_rotate_function(&attempt_1_rotate, attempt_1_rotate_descr);
    add_rotate_function(&attempt_2_rotate, attempt_2_rotate_descr);
    add_rotate_function(&attempt_3_rotate, attempt_3_rotate_descr);
    //add_rotate_function(&attempt_4_rotate, attempt_4_rotate_descr);
    add_rotate_function(&attempt_5_rotate, attempt_5_rotate_descr);
    add_rotate_function(&playGround_rotate, playGround_rotate_descr);
    
    
     
}


/***************
 * SMOOTH KERNEL
 **************/
 
/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* Compute min of two integers */
static int min(int a, int b) { return (a < b ? a : b);}

/* Compute max of two integers */
static int max(int a, int b) { return (a > b ? a : b);}

/* A struct used to compute averaged pixel value */
typedef struct {
    int red,green,blue,num;

} pixel_sum;

/* 
 * initialize_pixel_sum - Initializes all fields of sum to 0 
 */
static void initialize_pixel_sum(pixel_sum *sum){
    sum->red = sum->green = sum->blue = 0;
    sum->num = 0;
    
}

static void accumulate_sum(pixel_sum *sum, pixel p){
    sum->red += (int) p.red;
    sum->green += (int) p.green;
    sum->blue += (int) p.blue;
    sum->num++;
    
}
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) 
{
    current_pixel->red = (unsigned short) (sum.red/sum.num);
    current_pixel->green = (unsigned short) (sum.green/sum.num);
    current_pixel->blue = (unsigned short) (sum.blue/sum.num);
    return;
}
static pixel avg(int dim, int i, int j, pixel *src) 
{
    int ii, jj;
    pixel_sum sum;
    pixel current_pixel;
  
    initialize_pixel_sum(&sum);
    for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++) 
	    for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++) 
	      accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);
        assign_sum_to_pixel(&current_pixel, sum);
    return current_pixel;
}
 /* naive_smooth - The naive baseline version of smooth */

char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst) 
{
      int i, j, ii, jj;
    pixel_sum ps;
    
    for (j = 0; j < dim; j++){
        for (i = 0; i < dim; i++){
            initialize_pixel_sum(&ps);
            for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++){
                for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++){
                    accumulate_sum(&ps, src[RIDX(ii,jj,dim)]);
                }
            }
            dst[RIDX(i,j,dim)].red   = ps.red/ps.num;
            dst[RIDX(i,j,dim)].green = ps.green/ps.num;
            dst[RIDX(i,j,dim)].blue  = ps.blue/ps.num;
            
    //printf("num value for the inner most loop: %d\n", ps.num);  
        }
    //printf("num value for the mid i loop: %d\n", ps.num); 
    }
    //printf("num value for the outter j loop: %d\n", ps.num);


}

/******************************************************
 * Your different versions of the smooth kernel go here
 ******************************************************/

char attempt_1_smooth_descr[] = "ATTEMPT 1";
void attempt_1_smooth(int dim, pixel *src, pixel *dst) 
{
    int i, j;
    
    for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++)
        dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
        
}
char attempt_2_smooth_descr[] = "ATTEMPT 2";
void attempt_2_smooth(int dim, pixel *src, pixel *dst) 
{
  int i, j, tmp, tmp_i;
  //upper left
  dst[0].red = (src[0].red + src[1].red + src[dim].red + src[dim+1].red)>>2;
  dst[0].blue = (src[0].blue + src[1].blue + src[dim].blue + src[dim+1].blue)>>2;
  dst[0].green = (src[0].green + src[1].green + src[dim].green + src[dim+1].green)>>2;
  
  //upper right
  dst[dim-1].red = (src[dim-1].red + src[dim-2].red + src[dim *2 - 1].red + src[dim * 2-2].red)>>2;
  dst[dim-1].blue = (src[dim-1].blue + src[dim-2].blue + src[dim *2 - 1].blue + src[dim * 2-2].blue)>>2;
  dst[dim-1].green = (src[dim-1].green + src[dim-2].green + src[dim *2 - 1].green + src[dim * 2-2].green)>>2;

  //lower left
  dst[dim *(dim-1)].red = (src[dim*(dim-1)].red+ src[dim*(dim-1)+1].red+ src[dim*(dim-2)].red+ src[dim *(dim-2)+1].red)>>2;
  dst[dim *(dim-1)].blue = (src[dim*(dim-1)].blue+ src[dim*(dim-1)+1].blue+ src[dim*(dim-2)].blue+ src[dim *(dim-2)+1].blue)>>2;
  dst[dim *(dim-1)].green = (src[dim*(dim-1)].green+ src[dim*(dim-1)+1].green+ src[dim*(dim-2)].green+ src[dim *(dim-2)+1].green)>>2;
  

  //lower right
  dst[dim *dim-1].red = (src[dim*dim-1].red+src[dim*dim-2].red+ src[dim*(dim-1)-1].red+ src[dim*(dim -1)-2].red)>>2;
  dst[dim *dim-1].blue = (src[dim*dim-1].blue+src[dim*dim-2].blue+ src[dim*(dim-1)-1].blue+ src[dim*(dim -1)-2].blue)>>2;
  dst[dim *dim-1].green = (src[dim*dim-1].green+src[dim*dim-2].green+ src[dim*(dim-1)-1].green+ src[dim*(dim -1)-2].green)>>2;
   
  //upper edge, divide by 6
     for (j = 1; j < dim - 1; j++) 
    {
        dst[j].red = (src[j].red + src[j - 1].red + src[j + 1].red + 
                      src[j + dim].red + src[j + 1 + dim].red + src[j - 1 + dim].red) / 6;
        dst[j].blue = (src[j].blue + src[j - 1].blue + src[j + 1].blue + 
                       src[j + dim].blue + src[j + 1 + dim].blue + src[j - 1 + dim].blue) / 6;
        dst[j].green = (src[j].green + src[j - 1].green + src[j + 1].green + 
                        src[j + dim].green + src[j + 1 + dim].green + src[j - 1 + dim].green) / 6;
    }

  //lower edge
    for(j = dim *(dim-1)+1; j<dim*dim-1; j++) 
    {
        dst[j].red = (src[j].red + src[j-1].red + src[j + 1].red + src[j - dim].red + src[j + 1 - dim].red + src[j - 1 - dim].red) / 6;
        dst[j].blue = (src[j].blue + src[j - 1].blue + src[j + 1].blue + src[j - dim].blue + src[j + 1 - dim].blue + src[j - 1 - dim].blue) / 6;
        dst[j].green = (src[j].green + src[j - 1].green + src[j + 1].green + src[j - dim].green + src[j + 1 - dim].green + src[j - 1 - dim].green) / 6;
    } 

    //left edge
    for (j = dim; j<dim* (dim - 1); j += dim) 
    {
        dst[j].red = (src[j].red + src[j-dim].red+src[j+1].red+src[j+dim].red + src[j+1 + dim].red + src[j - dim + 1].red) / 6;
        dst[j].blue = (src[j].blue + src[j - dim].blue + src[j + 1].blue + src[j + dim].blue + src[j + 1 + dim].blue + src[j - dim + 1].blue) / 6;
        dst[j].green = (src[j].green + src[j - dim].green + src[j + 1].green + src[j + dim].green + src[j + 1 + dim].green + src[j - dim + 1].green) / 6;
    }

    //right edge
    for (j = dim+dim-1; j<dim*dim-1; j+=dim){
        dst[j].red = (src[j].red+src[j-1].red+src[j-dim].red+src[j+dim].red+src[j-dim-1].red+src[j-1+dim].red)/6;
        dst[j].blue = (src[j].blue+src[j-1].blue+src[j-dim].blue+src[j+dim].blue+src[j-dim-1].blue+src[j-1+dim].blue)/6;
        dst[j].green = (src[j].green+src[j-1].green+src[j-dim].green+src[j+dim].green+src[j-dim-1].green+src[j-1+dim].green)/6;
    }
    //center

    tmp_i = dim;
    for(i = 1; i<dim-1; i++){
        for(j = 1; j<dim-1; j++){
          tmp = tmp_i+j;
          dst[tmp].red = (src[tmp].red + src[tmp-1].red + src[tmp+1].red+src[tmp-dim].red+src[tmp-dim-1].red+ 
                            src[tmp-dim+1].red+src[tmp+dim].red+src[tmp+dim+1].red+src[tmp+dim-1].red)/9;

          dst[tmp].blue = (src[tmp].blue+src[tmp-1].blue+src[tmp+1].blue+src[tmp-dim].blue + src[tmp-dim-1].blue+
                          src[tmp-dim+1].blue+src[tmp+dim].blue+src[tmp+dim+1].blue+src[tmp+dim-1].blue)/9;

          dst[tmp].green = (src[tmp].green+src[tmp-1].green+src[tmp+1].green+src[tmp-dim].green +src[tmp+dim].green+
                          src[tmp-dim+1].green+src[tmp-dim-1].green+src[tmp+dim+1].green+src[tmp+dim-1].green)/9;
        }
      tmp_i+=dim;
    }
        
}

/******************************************************
 * NOTES!!!!!
1) look at helper functions, see if we can optimize them
   - max and min (optimized into single return statement
   - initlaize pixels, set RGB equal to each other and the last = 0, saves on deceleration
   - added a function to average the pixels rather then doing so in the loop
2) start unrolling the loops (MOVED FROM THE INSIDE OF NAIVE FUNCTION)
can perform loop tiling/loop strip mining of the loops, by dividing the matrix/image in 
square tiles and smoothing one tile at a time. This way we achieve better cache utilization.
  -this involves taking the average of all 4 (ps.num for the outter loop), 6(ps.num for the mid loop) and 9(ps.num for inner most loop)
     pixels in our unrolling process. and insted of dividing by 4, we can get further optimization by >>
  - to further optimize, we can break the image into 9 quadrents:
        i)upper right X
        ii) upper left X
        iii) lower right X
        iv) lower left X
        v)upper  edge X
        vi) lower edge X
        vii)  left edge X
        viii) right edge X
        ix) cenfer X
 ******************************************************/

 /* smooth - Your current working version of smooth. 
 * IMPORTANT: This is the version you will be graded on
 */
char smooth_descr[] = "smooth: Current working version";
void smooth(int dim, pixel *src, pixel *dst) 
{
    naive_smooth(dim, src, dst);
    attempt_1_smooth(dim, src, dst);
    attempt_2_smooth(dim, src, dst);
}


/********************************************************************* 
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_smooth_functions() {
    add_smooth_function(&smooth, smooth_descr);
    add_smooth_function(&naive_smooth, naive_smooth_descr);
    add_smooth_function(&attempt_1_smooth, attempt_1_smooth_descr);
    add_smooth_function(&attempt_2_smooth, attempt_2_smooth_descr);
    /* ... Register additional test functions here */
}

