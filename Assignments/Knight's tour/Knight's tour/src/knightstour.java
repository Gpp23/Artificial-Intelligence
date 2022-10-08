public class knightstour {
    public static int N = 5;
    public static int BOARD[][] = new int [N][N] ;
    public static int CX[] = new int[8];
    public static int CY[] = new int[8];
    public static boolean YES;

    public static void Initialize(){
        CX[0] = 2; 
        CY[0] = 1;
        CX[1] = 1; 
        CY[1] = 2;
        CX[2] = -1; 
        CY[2] = 2;
        CX[3] = -2; 
        CY[3] = 1;
        CX[4] = -2; 
        CY[4] = -1;
        CX[5] = -1; 
        CY[5] = -2;
        CX[6] = 1; 
        CY[6] = -2;
        CX[7] = 2; 
        CY[7] = -1;

        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                BOARD[i][j] = 0;
            }
        }
    }

    public static void TRY(int L, int X, int Y, boolean YES){
        int K = 0; //Production number
        int U,V; //New knight's position
        do{
            //System.out.println("K= " + K);
            U = X + CX[K]; 
            V = Y + CY[K];
            if(U >= 0 && U < N && V >= 0 && V < N){
                if(BOARD[U][V] == 0){
                    BOARD[U][V] = L;
                    if(L < N*N){
                        TRY(L+1, U, V, YES);
                        if(!YES) BOARD[U][V] = 0;
                    }
                }else{
                    YES = true;
                }
            }
            K++;
        }while(YES || K == 8);
    }


    public static void main(String[] args) throws Exception {
        Initialize();
        YES = false;
        BOARD[0][0] = 1;
        TRY(2, 0, 0, YES);
        if(YES){
            for(int i = N - 1; i >= 0; i++){

                for(int j = 1; j < N; j++){
                    System.out.print(BOARD[j][i] + " ");
                }
                System.out.println();
            }
        }else{
            System.out.println("Path does not exist.");
            for(int i = N - 1; i >= 0; i--){

                for(int j = 0; j < N; j++){
                    System.out.print(BOARD[j][i] + " ");
                }
                System.out.println();
            }
        }
    }
}
