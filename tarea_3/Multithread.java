import java.io.File;  // Import the File class
import java.io.FileNotFoundException;  // Import this class to handle errors
import java.util.Scanner; // Import the Scanner class to read text files

public class Multithread{
    public static class Hebra extends Thread{
        public void Multithread_cuaternaria(int N, int M, int[][] matrix, int x, int y){
            if(M == N){
                for (int i=0;i<M;i=i+1){
                    if (matrix[i][0] ==1){
                        System.out.print("fila "+(x+i+1)+ ", columna");
                        System.out.println(" ["+(y+1)+","+(y+M)+"]");
                    }
                }
                return;
            }
            else{
                int limit = N/2;
                int c1[][] = new int[N][N];
                int c2[][] = new int[N][N];
                int c3[][] = new int[N][N];
                int c4[][] = new int[N][N];

                for (int i=0;i<limit;i=i+1){
                    for (int j=0;j<limit;j=j+1){
                        c1[i][j] = matrix[i][j];
                        c2[i][j] = matrix[i+limit][j];
                        c3[i][j] = matrix[i][j+limit];
                        c4[i][j] = matrix[i+limit][j+limit];
                    }
                }   

                Hebra thread1 = new Hebra();
                Hebra thread2 = new Hebra();
                Hebra thread3 = new Hebra();
                Hebra thread4 = new Hebra();
                
                thread1.start();
                thread2.start();
                thread3.start();
                thread4.start();
                
                thread1.Multithread_cuaternaria(limit,M,c1,x,y);
                thread2.Multithread_cuaternaria(limit,M,c2,x+limit, y);
                thread3.Multithread_cuaternaria(limit,M,c3,x,y+limit);
                thread4.Multithread_cuaternaria(limit,M,c4,x+limit,y+limit);
            }
        }
    }
    public static void main(String[] args) {
        int matrix[][];
        try {
        File f1 = new File(args[0]);
        Scanner myReader = new Scanner(f1);
        int N = Integer.parseInt(myReader.nextLine());
        int M = Integer.parseInt(myReader.nextLine());
        String [] aux = new String[N];
        String [] aux2 = new String[N];
        matrix = new int[N][N];
        aux = myReader.nextLine().split(",");
        myReader.close();

        int contador = 0;
        int contador2 = 0;
        for(String i: aux){
            contador2 = 0;
            aux2 = i.replaceAll("[\\[|\\]]", "").split(" ");
            for(String j: aux2){
                matrix[contador][contador2] = Integer.parseInt(j);
                contador2 = contador2+1;
            }
            contador = contador+1;
        }

        // start de contar tiempo
        long startTime = System.nanoTime();
        Hebra thread1 = new Hebra();

        thread1.Multithread_cuaternaria(N,M,matrix,0,0);

        // end
        long elapsedTime = System.nanoTime() - startTime;

        //System.out.println(elapsedTime);
        } catch (FileNotFoundException e) {
            System.out.println("Ocurrio un error en la lectura del archivo");
            e.printStackTrace();
        }
    }

}
