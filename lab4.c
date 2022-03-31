# include <omp.h>
# include <stdio.h>
int main(){
int var1 , var2 , var3 ;

printf ( " Liczba wą tk ów: %d \n" , omp_get_num_threads() ) ;
printf ( " Jestem wą tek nr %d\n " , omp_get_thread_num() ) ;
printf ( "\n" ) ;

#pragma omp parallel private ( var1 , var2 ) shared ( var3 )
{
    printf ( " Liczba wą tk ów: %d\n" , omp_get_num_threads()) ;
    printf ( " Jestem wą tek nr %d\n" , omp_get_thread_num()) ;

}
printf ( "\n " ) ;

printf ( " Liczba wą tk ów: %d \n" , omp_get_num_threads()) ;
printf ( " Jestem wą tek nr %d\n" , omp_get_thread_num()) ;
return 0;
}