using System;

namespace ComplexMath
{	 
	public struct ComplexNumber : IComparable 
    {
        static readonly private double halfOfRoot2 = 0.5 * Math.Sqrt(2);
        static readonly public ComplexNumber Zero = new ComplexNumber(0, 0);
        static readonly public ComplexNumber I = new ComplexNumber(0, 1);
        static readonly public ComplexNumber MaxValue = new ComplexNumber(double.MaxValue, double.MaxValue);
        static readonly public ComplexNumber MinValue = new ComplexNumber(double.MinValue, double.MinValue);	  
      
        public double Real;         
        public double Imaginary;
               
        public ComplexNumber(double real, double imaginary)
        {
            this.Real = (double)real;
            this.Imaginary = (double)imaginary;
        }

        public ComplexNumber(ComplexNumber c)
        {
            this.Real = c.Real;
            this.Imaginary = c.Imaginary;
        }

        static public ComplexNumber CreateFromRealAndImaginary(double real, double imaginary)
        {
            ComplexNumber c;
            c.Real = (double)real;
            c.Imaginary = (double)imaginary;
            return c;
        }
         
        static public ComplexNumber CreateFromModulusAndArgument(double modulus, double argument)
        {
            ComplexNumber c;
            c.Real = (double)(modulus * Math.Cos(argument));
            c.Imaginary = (double)(modulus * Math.Sin(argument));
            return c;
        }
    
        static public ComplexNumber Sqrt(ComplexNumber c)
        {
            double x = c.Real;
            double y = c.Imaginary;
            double modulus = Math.Sqrt(x * x + y * y);

            int sign = (y < 0) ? -1 : 1;

            c.Real = (double)(halfOfRoot2 * Math.Sqrt(modulus + x));
            c.Imaginary = (double)(halfOfRoot2 * sign * Math.Sqrt(modulus - x));

            return c;
        }
                
        static public ComplexNumber Pow(ComplexNumber c, double exponent)
        {
            double x = c.Real;
            double y = c.Imaginary;

            double modulus = Math.Pow(x * x + y * y, exponent * 0.5);
            double argument = Math.Atan2(y, x) * exponent;

            c.Real = (double)(modulus * System.Math.Cos(argument));
            c.Imaginary = (double)(modulus * System.Math.Sin(argument));

            return c;
        }
      	    
		public double GetModulus() 
        {
			double	x	= this.Real;
			double	y	= this.Imaginary;
			return	(double) Math.Sqrt( x*x + y*y );
		}
		 
		public double GetModulusSquared() 
        {			 
            return (double)this.Real * this.Real + this.Imaginary * this.Imaginary;
		}
	 
		public double GetArgument() 
        {
			return (double) Math.Atan2( this.Imaginary, this.Real );
		}
	 	 
		public ComplexNumber GetConjugate() 
        {
			return CreateFromRealAndImaginary( this.Real, -this.Imaginary );
		}
	  
		public void Normalize() 
        {
			double	modulus = this.GetModulus();
			if( modulus == 0 ) 
            {
				throw new DivideByZeroException();
			}
			this.Real	= (double)( this.Real / modulus );
			this.Imaginary	= (double)( this.Imaginary / modulus );
		}
	  
		public static explicit operator ComplexNumber ( double d ) 
        {
			ComplexNumber c;
			c.Real	= (double) d;
			c.Imaginary	= (double) 0;
			return c;
		}
         
		public static explicit operator double ( ComplexNumber c ) 
        {
			return (double) c.Real;
		}
			 
		public static bool	operator==( ComplexNumber a, ComplexNumber b ) 
        {
			return	( a.Real == b.Real ) && ( a.Imaginary == b.Imaginary );
		}
		 
		public static bool	operator!=( ComplexNumber a, ComplexNumber b )
        {
			return	( a.Real != b.Real ) || ( a.Imaginary != b.Imaginary );
		}
	 
		public override int	GetHashCode() 
        {
			return	( this.Real.GetHashCode() ^ this.Imaginary.GetHashCode() );
		}
 
		public override bool Equals( object o )
        {
			if( o is ComplexNumber ) 
            {
				ComplexNumber c = (ComplexNumber) o;
				return  ( this == c );
			}
			return	false;
		}
		 
		public int	CompareTo( object o ) 
        {
			if( o == null ) 
            {
				return 1; 
			}
			else if( o is ComplexNumber ) 
            {
				return	this.GetModulus().CompareTo( ((ComplexNumber)o).GetModulus() );
			}
            else if (o is double) 
            {
				return	this.GetModulus().CompareTo( (double)o );
			}
            else if (o is float) 
            {
				return	this.GetModulus().CompareTo( (float)o );
			}
			throw new ArgumentException();
		}
	 	 
		public static ComplexNumber operator+( ComplexNumber a ) 
        {
			return a;
		}

        public static ComplexNumber operator +(ComplexNumber a, double f)
        {
            a.Real = (double)(a.Real + f);
            return a;
        }

        public static ComplexNumber operator +(double f, ComplexNumber a)
        {
            a.Real = (double)(a.Real + f);
            return a;
        }

        public static ComplexNumber operator +(ComplexNumber a, ComplexNumber b)
        {
            a.Real = a.Real + b.Real;
            a.Imaginary = a.Imaginary + b.Imaginary;
            return a;
        }

		public static ComplexNumber operator-( ComplexNumber a ) 
        {
			a.Real	= -a.Real;
			a.Imaginary	= -a.Imaginary;
			return a;
		}
 	 
		public static ComplexNumber operator-( ComplexNumber a, double f ) 
        {
			a.Real	= (double)( a.Real - f );
			return a;
		}
 
		public static ComplexNumber operator-( double f, ComplexNumber a ) 
        {
			a.Real	= (float)( f - a.Real );
			a.Imaginary	= (float)( 0 - a.Imaginary );
			return a;
		}
	 
		public static ComplexNumber operator-( ComplexNumber a, ComplexNumber b ) 
        {
			a.Real	= a.Real - b.Real;
			a.Imaginary	= a.Imaginary - b.Imaginary;
			return a;
		}
		 
		public static ComplexNumber operator*( ComplexNumber a, double f ) 
        {
			a.Real	= (double)( a.Real * f );
			a.Imaginary	= (double)( a.Imaginary * f );
			return a;
		}
			 
		public static ComplexNumber operator*( double f, ComplexNumber a ) 
        {
			a.Real	= (double)( a.Real * f );
			a.Imaginary	= (double)( a.Imaginary * f );			
			return a;
		}
	 
		public static ComplexNumber operator*( ComplexNumber a, ComplexNumber b ) 
        {
			double	x = a.Real, y = a.Imaginary;
			double	u = b.Real, v = b.Imaginary;			
			a.Real	= (double)( x*u - y*v );
			a.Imaginary	= (double)( x*v + y*u );			
			return a;
		}
	 
		public static ComplexNumber operator/( ComplexNumber a, double f ) 
        {
			if( f == 0 ) 
            {
				throw new DivideByZeroException();
			}
			
			a.Real	= (double)( a.Real / f );
			a.Imaginary	= (double)( a.Imaginary / f );
			
			return a;
		}
				 
		public static ComplexNumber operator/( ComplexNumber a, ComplexNumber b ) 
        {
			double	x = a.Real,	y = a.Imaginary;
			double	u = b.Real,	v = b.Imaginary;
			double	denom = u*u + v*v;

			if( denom == 0 ) 
            {
				throw new DivideByZeroException();
			}

			a.Real	= (double)( ( x*u + y*v ) / denom );
			a.Imaginary	= (double)( ( y*u - x*v ) / denom );
			
			return a;
		}
	  
		public override string ToString() 
        {
			return	String.Format( "( {0}, {1}i )", this.Real, this.Imaginary );
		}
	  
		static public bool IsEqual( ComplexNumber a, ComplexNumber b, double tolerance )
        {
		    return  ( Math.Abs( a.Real - b.Real ) < tolerance ) &&
				    ( Math.Abs( a.Imaginary - b.Imaginary ) < tolerance );
		}

     
	}

}
