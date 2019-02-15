/*A PROGRAM TO CREATE GRAPHS OF SHOCKLEY'S DIODE EQUATION*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<graphics.h>//Necessary header file for a graphics input
#include<conio.h>
float Q,K,T,T2,I1,V,vmax,vinterval,arra[2][450],xsum=0.0;//external variables declarations for reducing parameters
int n,i,j,p,arr[450],f,g,res,errorcode;                  //passing and subsequent checkings to respective functions
char ar[100],fname[]="Grapha.txt",vol[]="VOLTAGE",cur[]="CURRENT";
int graph();        //functions declarations
int makefile();
int main()
{
Q=1.6e-19;      //Electronic charge (q)
K=1.38e-23;     //Boltzmann constant
I1=3e-8;        //Saturation current
T=298.0;        //Room temperature in Kelvin
n=2;            //n=1:Germanium, n=2:Silicon
vmax=0.9;       //Maximum applied voltage
vinterval=0.9/450;      //Dividing the max voltage to the number of pixels chosen horizontally for plotting the graph
printf("\nThe maximum voltage across the diode is chosen to be : %f\n",vmax);
printf("\nThe saturation current is chosen to be %g\n",I1);
printf("\nThe temperature is chosen to be 25'C\n");
int gd=0,gm;    //initialising graphics driver and graphics mode
initgraph(&gd,&gm," ");     //initiating the graphics window
errorcode=graphresult();    //returns an integer value to errorcode if some error exists
if(errorcode!=grOk)         //error checking
{
    printf("\nGraphics error : %s\n",grapherrormsg(errorcode));//coverts the integer value to a readable string indicating a particular error
    printf("\nPress any key to exit.");
    getch();
    exit(1);
}
outtextxy(60,463,"Voltage across the diode (Vd ) in volts");
settextstyle(0,VERT_DIR,0);
outtextxy(35,460,"Current (Id) in mA");
line(60,460,620,460);   //X-axis plotting
line(60,5,60,460);      //Y-axis plotting
line(615,455,620,460);  //Necessary lines are drawn to make the axes and markings visible
line(615,465,620,460);
line(55,10,60,5);
line(65,10,60,5);
circle(55,465,4);
line(305,470,380,470);
line(375,465,380,470);
line(375,475,380,470);
line(45,200,45,275);
line(40,205,45,200);
line(50,205,45,200);
graph();    //Call to graph function which calculates the diode current and contains the efficient logic to plot the required graph
printf("\nDo you want to plot another graph? (1/0) :");
scanf("%d",&f);
while(f==0)
{
    printf("\nExecution stopped, Press '1' to exit graph :");
    scanf("%d",&f);
    if(f==1)
        exit(1);
}
while(f)
{
    printf("\nEnter the temperature : ");   //Entering new temperature
    scanf("%f",&T2);
    T2=T2+273.0;
    I1=I1*(pow(2,((T2-T)/10))); //Calculating the equivalent saturation current w.r.t to the saturation current at 25'C
    T=T2;
graph();    //Call to graph function for plotting
printf("\nDo you want to plot another graph? (1/0) :");
scanf("%d",&f);
while(f==0)
{
    printf("\nExecution stopped, Press '1' to exit graph :");
    scanf("%d",&f);
    if(f==1)
        exit(1);
}
}
getch();
closegraph();   //function that closes all graphics operations
return 0;
}       //END OF MAIN FUNCTION
int graph() //Pivotal function to carry out all logical and graphical plotting operations
{   ++g;    //count for the number of graphs to be plotted
    xsum=0.0;   //xsum deals with the diode voltage of each interval
for(i=0;i<450;i++)  //Loop to generate the equivalent diode current for corresponding diode voltages
    {
    arra[0][i]=xsum;        //First row of arra contains diode voltages
    xsum=xsum+vinterval;    //xsum gets incremented by vinterval
    arra[1][i]=I1*(exp((Q*arra[0][i])/(2*K*T))-1);  //Second row of arra contains diode currents
    }
for(i=0;i<450;i++)  //Loop to approximate the pixel corresponding to each diode voltage and current
{                           //Graphics window size is 640 X 480 pixels
for(j=0;j<450;j++)          //Plottable pixels on this window is 450 X 450
    if(arra[1][i]<arra[0][j])
    {
    p=j;
    j=450;
    }
if((arra[1][i]-arra[0][p-1])<(arra[0][p]-arra[1][i]))
    arr[i]=450-(p-1);
else
    arr[i]=450-p;
}
moveto(60,460); //moveto moves the current pointer to the specified pixel
for(i=0;i<450;i++)
    lineto(i+60,arr[i]+10);     //lineto joins two specified points in pixels
printf("\nDo you want your observations to be written into a text file? (1/0) :");
scanf("%d",&res);
if(res==1)
{
res=makefile();
if(res==1)  //Returns 1 if file writing is sucessful else it returns 0
    printf("\nFile written successfully with file name %s.\n",fname);
else
    printf("\nFile writing unsuccessful.\n");
}
return 1;
}
int makefile()      //A function to record the corresponding observations in a text file
{
FILE *fp;
if((g!=1)&&(fname[5]<122))  //Logic to set the filename automatically
    fname[5]=fname[5]+1;
fp=fopen(fname,"w+");
if(fp==NULL)
{
    printf("\nFile cannot be opened.\n");
    return 0;
}
sprintf(ar,"\nThe following observations is of the graph with :\nTemperature= %e and Saturation current= %e\n\n",T,I1);
fputs(ar,fp);
fprintf(fp,"    %s              %s\n\n",vol,cur);
for(i=0;i<450;i++)
    fprintf(fp,"%e ----- %e\n",arra[0][i],arra[1][i]);
fclose(fp);
return 1;
}//End of the program
