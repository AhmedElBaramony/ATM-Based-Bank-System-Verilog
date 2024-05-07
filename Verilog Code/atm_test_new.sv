`timescale 1ns/1ps

module ATM_test;
    //INPUTS
    reg clk,rst;
    reg [11:0] Account_Number, PIN,Destination_Account; 
	reg [11:0] WithDraw_Amount,Transfer_Amount;
	reg [11:0] Deposit_Amount;
	reg [2:0] Operation;
    

    //OUTPUTS
    reg [11:0] FinalBalance;
	reg [11:0] Final_DstBalance;

	
   

    //INISTANCE OF ATM
    ATM A1(clk,rst,Account_Number,PIN,Destination_Account,
    WithDraw_Amount,Transfer_Amount,Deposit_Amount,Operation,1'b1,
    FinalBalance,Final_DstBalance);

     integer fd;
    initial fd = $fopen("outputs.txt","w");

    //CLOCK GENERATION
    initial begin
    clk=1'b0;
    forever begin
    #1 clk=~clk;
    end
end

initial begin
    rst=0;
    Account_Number<=12'h000;
    PIN<=12'h000;
    Destination_Account<=12'h000;
    Operation<=0;
    Deposit_Amount<=12'h000;
    Transfer_Amount<=12'h000;
    WithDraw_Amount<=12'h000;

    @(negedge clk);
     rst=1;
    @(negedge clk);
    if (FinalBalance != 0) begin
        $display ("Clear has a Problem");
    end
    rst<=0;
    Account_Number<=12'hffa;
    PIN<=12'h729;
    Destination_Account<=12'hffe;

    repeat(3) @(negedge clk);
    
    Account_Number=12'hfff;
    PIN=12'hff1;
    Destination_Account<=12'h456;
    repeat(3) @(negedge clk);
    PIN=12'hfff;
    Operation<=0;
    Deposit_Amount<=12'h11f;
    Transfer_Amount<=12'h012;
    WithDraw_Amount<=12'h013;

    repeat(4) @(negedge clk);

    Operation<=1;
    
    repeat(5) @(negedge clk);
    
    Operation<=2;
    
    repeat(3) @(negedge clk);
    
    Operation<=0;
    
    repeat(4) @(negedge clk);
    
    Operation<=3;
    
    repeat(5) @(negedge clk);
    
    Deposit_Amount<=12'h11f;
    Transfer_Amount<=12'hffe;
    WithDraw_Amount<=12'hffe;
    
    Operation<=1;
    
    repeat(4) @(negedge clk);
    
    Operation<=2;
    
    repeat(3) @(negedge clk);
    
    Operation<=0;
    
    repeat(4) @(negedge clk);
    
    Operation<=3;
    
    repeat(4) @(negedge clk);

    Operation<=6;

    repeat (2) @(negedge clk);

    $fwrite(fd,"Final Balance: %d\n", FinalBalance);
    $fwrite(fd,"Final destination Balance: %d\n", Final_DstBalance);
    
    Operation<=4;
    
    repeat(4) @(negedge clk);

    rst=0;
    Account_Number<=12'h000;
    PIN<=12'h000;
    Destination_Account<=12'h000;
    Operation<=0;
    Deposit_Amount<=12'h000;
    Transfer_Amount<=12'h000;
    WithDraw_Amount<=12'h000;
    @(negedge clk);
    
// psl assert never (A1.next_state == A1.S12 && A1.current_state == A1.S8 &&  A1.F == 0) @(negedge clk);

// psl assert never (A1.next_state == A1.S12 && A1.current_state == A1.S6 &&  A1.WithDraw_Amount == 0) @(negedge clk);

// psl assert never (A1.next_state == A1.S10 && A1.current_state == A1.S5 &&  A1.Deposit_Amount == 0) @(negedge clk);

// psl assert never (A1.next_state == A1.S4 && A1.current_state == A1.S2 &&  A1.VP == 0) @(negedge clk);

// psl assert never ((A1.op != 3'b000) && (A1.next_state == A1.S5)) @(negedge A1.clk);

// psl assert never ((A1.op != 3'b001) && (A1.next_state == A1.S6)) @(negedge A1.clk);

// psl assert never ((A1.op != 3'b010) && (A1.next_state == A1.S7)) @(negedge A1.clk);

// psl assert never ((A1.op != 3'b011) && (A1.next_state == A1.S8)) @(negedge A1.clk);

    $stop();
end
endmodule