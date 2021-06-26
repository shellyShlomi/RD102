int main()
{
    int strtod_res_as_int = 3;
    double is_fracture =  strtod_res_as_int/ 3;

    printf("%d \t %f\n",strtod_res_as_int, is_fracture);

strtod_res_as_int = 0.5;

is_fracture =  strtod_res_as_int/ 0.5;
    printf("%d \t %f\n",strtod_res_as_int, is_fracture);


strtod_res_as_int = 1000.5;

is_fracture =  strtod_res_as_int/ 1000.5;
    printf("%d \t %f\n",strtod_res_as_int, is_fracture);


    return (0);
}