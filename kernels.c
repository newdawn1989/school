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
    for (i = 0; i < dim; i++){
        for (j = 0; j < dim; j++){
            dst[RIDX(dim-1-j, i, dim)].red   = src[RIDX(i, j, dim)].red;
            dst[RIDX(dim-1-j, i, dim)].green = src[RIDX(i, j, dim)].green;
            dst[RIDX(dim-1-j, i, dim)].blue  = src[RIDX(i, j, dim)].blue;
        
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

char attempt_1_rotate_descr[] = "Attempt 1";
void attempt_1_rotate(int dim, pixel *src, pixel *dst) 
{
    
    
        int i, j;
    for (i = 0; i < dim; i+=4){
        for (j = 0; j < dim; j+=4){
            dst[RIDX(dim-1-0, i, dim)]   = src[RIDX(i, 0, dim)];
            dst[RIDX(dim-1-1, i, dim)]   = src[RIDX(i, 1, dim)];
            dst[RIDX(dim-1-2, i, dim)]   = src[RIDX(i, 2, dim)];
            dst[RIDX(dim-1-3, i, dim)]   = src[RIDX(i, 3, dim)];
        }
    }

}

char playGround_rotate_descr[] = "PLAYGROUND======optimize array index cacheing";
void playGround_rotate(int dim, pixel *src, pixel *dst) 
{	
    //You should think of I[RIDX(i,j,n)] as equivalent to I[i][j]
int i, j, j1;
		int T = 32;
		for(i = 0; i < dim; i+=T)
			for(j = 0; j < dim; j+=T)
				for(j1 = j; j1 < j+T; j1++) {
					dst[RIDX(dim-1-j1, i+0, dim)] = src[RIDX(i+0, j1, dim)];
					dst[RIDX(dim-1-j1, i+1, dim)] = src[RIDX(i+1, j1, dim)];
					dst[RIDX(dim-1-j1, i+2, dim)] = src[RIDX(i+2, j1, dim)];
					dst[RIDX(dim-1-j1, i+3, dim)] = src[RIDX(i+3, j1, dim)];
					dst[RIDX(dim-1-j1, i+4, dim)] = src[RIDX(i+4, j1, dim)];
					dst[RIDX(dim-1-j1, i+5, dim)] = src[RIDX(i+5, j1, dim)];
					dst[RIDX(dim-1-j1, i+6, dim)] = src[RIDX(i+6, j1, dim)];
					dst[RIDX(dim-1-j1, i+7, dim)] = src[RIDX(i+7, j1, dim)];
					dst[RIDX(dim-1-j1, i+8, dim)] = src[RIDX(i+8, j1, dim)];
					dst[RIDX(dim-1-j1, i+9, dim)] = src[RIDX(i+9, j1, dim)];
					dst[RIDX(dim-1-j1, i+10, dim)] = src[RIDX(i+10, j1, dim)];
					dst[RIDX(dim-1-j1, i+11, dim)] = src[RIDX(i+11, j1, dim)];
					dst[RIDX(dim-1-j1, i+12, dim)] = src[RIDX(i+12, j1, dim)];
					dst[RIDX(dim-1-j1, i+13, dim)] = src[RIDX(i+13, j1, dim)];
					dst[RIDX(dim-1-j1, i+14, dim)] = src[RIDX(i+14, j1, dim)];
					dst[RIDX(dim-1-j1, i+15, dim)] = src[RIDX(i+15, j1, dim)];
					dst[RIDX(dim-1-j1, i+16, dim)] = src[RIDX(i+16, j1, dim)];
					dst[RIDX(dim-1-j1, i+17, dim)] = src[RIDX(i+17, j1, dim)];
					dst[RIDX(dim-1-j1, i+18, dim)] = src[RIDX(i+18, j1, dim)];
					dst[RIDX(dim-1-j1, i+19, dim)] = src[RIDX(i+19, j1, dim)];
					dst[RIDX(dim-1-j1, i+20, dim)] = src[RIDX(i+20, j1, dim)];
					dst[RIDX(dim-1-j1, i+21, dim)] = src[RIDX(i+21, j1, dim)];
					dst[RIDX(dim-1-j1, i+22, dim)] = src[RIDX(i+22, j1, dim)];
					dst[RIDX(dim-1-j1, i+23, dim)] = src[RIDX(i+23, j1, dim)];
					dst[RIDX(dim-1-j1, i+24, dim)] = src[RIDX(i+24, j1, dim)];
					dst[RIDX(dim-1-j1, i+25, dim)] = src[RIDX(i+25, j1, dim)];
					dst[RIDX(dim-1-j1, i+26, dim)] = src[RIDX(i+26, j1, dim)];
					dst[RIDX(dim-1-j1, i+27, dim)] = src[RIDX(i+27, j1, dim)];
					dst[RIDX(dim-1-j1, i+28, dim)] = src[RIDX(i+28, j1, dim)];
					dst[RIDX(dim-1-j1, i+29, dim)] = src[RIDX(i+29, j1, dim)];
					dst[RIDX(dim-1-j1, i+30, dim)] = src[RIDX(i+30, j1, dim)];
					dst[RIDX(dim-1-j1, i+31, dim)] = src[RIDX(i+31, j1, dim)];
				}
}

/*

====NOTES=======
STEPS
1) optimize for loops

   - performing loop unrolling for the inner loop, rather then doing an 32 factor unrollilng.
   - sets static variable for the dimension of the unrolliing so it is not recalcualted over and over T = 32;
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
    //add_rotate_function(&attempt_1_rotate, attempt_1_rotate_descr);
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
char attempt_2_smooth_descr[] = "ATTEMPT 1";
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
        v)upper  edge
        vi) lower edge
        vii)  left edge
        viii) right edge
        ix) cenfer
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

