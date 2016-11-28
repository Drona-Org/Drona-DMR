model type float32 = int;

/** Constructors **/
//// Assign the float value
model fun AssignFloat32(lhs: float32, rhs: float32)
{
   lhs = rhs;
}

//// Converts an integer to float
model fun IntToFloat32(val: int) : float32
{
   return val; 
} 

//// Converts scientific notation to a float (mantissa * 10^exp) 
//// If exponent is too small or too large, then returns (negative) infinity
model fun ScientificToFloat32 (mantissa: int, exp: int) : float32
{
   var index : int;
   var val : int;
   val = 10;
   index = 0;
   while(index < exp)
   {
      val = val * 10;
      index = index + 1;
   }
   return mantissa * val;
} 

/** Arithmetic operations **/
model fun NegFloat32(op1: float32) : float32
{
   return -op1;
} 

model fun AddFloat32(op1: float32, op2: float32) : float32
{
   return op1 + op2;
} 

model fun SubFloat32(op1: float32, op2: float32) : float32
{
   return op1 - op2;
} 

model fun MulFloat32(op1: float32, op2: float32) : float32
{
   return op1 * op2;
} 

model fun DivFloat32(op1: float32, op2: float32) : float32
{
   return op1/op2;
} 

model fun AbsFloat32(op1: float32, op2: float32) : float32
{
   //not implemented
   assert false;
   return default(float32);
} 

model fun NaNFloat32() : float32 {
   return 0;
}


/** Testers **/
model fun IsNaNFloat32(op1: float32) : bool
{
   return $;
} 

model fun IsInftyFloat32(op1: float32) : bool
{
   return $;
} 

model fun IsPosInftyFloat32(op1: float32) : bool
{
   return $;
} 

model fun IsNegInftyFloat32(op1: float32) : bool
{
   return $;
} 

model fun IsFiniteFloat32(op1: float32) : bool
{
   return $;
} 

model fun IsEqFloat32(op1: float32, op2: float32) : bool
{
   return op1 == op2;
} 

model fun IsNearFloat32(op1: float32, op2: float32, epsilon:float32) : bool
{
   if(op1 > op2)
      return (op1 - op2) < epsilon;
   else 
      return (op2 - op1) < epsilon;
} 

model fun IsNEqFloat32(op1: float32, op2: float32) : bool
{
   return op1 != op2;
} 

model fun IsLtFloat32(op1: float32, op2: float32) : bool
{
   return op1 < op2;
} 

model fun IsGtFloat32(op1: float32, op2: float32) : bool
{
   return op1 > op2;
} 

model fun IsLeFloat32(op1: float32, op2: float32) : bool
{
   return op1 <= op2;
} 

model fun IsGeFloat32(op1: float32, op2: float32) : bool
{
   return op1 >= op2;
} 
