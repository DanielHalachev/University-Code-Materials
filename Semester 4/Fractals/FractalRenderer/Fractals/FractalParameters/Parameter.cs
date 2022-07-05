using System;

namespace FractalRenderer
{
    public class Parameter
    {
        private readonly string name = string.Empty;
        private object value = null;

        public Parameter(string name, object value)
        {
            this.name = name;
            this.value = value;
        }

        public string Name
        {
            get { return name; }
        }

        public object Value
        {
            get { return value; }
            set { this.value = value; }
        }

        public Type Type
        {
            get { return this.value.GetType(); }
        }
    }

}
