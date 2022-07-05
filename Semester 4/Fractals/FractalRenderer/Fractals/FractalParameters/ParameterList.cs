using System;
using System.Collections;
using System.Collections.Generic;

namespace FractalRenderer
{
    public class ParameterList : IFractalParameters
    {
        private List<Parameter> parameterList = new List<Parameter>();

        public IEnumerator GetEnumerator()
        {
            return this.parameterList.GetEnumerator();
        }

        public object Clone()
        {
            ParameterList parameterSet = new ParameterList();
            foreach (Parameter px in parameterList)
            {
                parameterSet.AddValue(px.Name, px.Value);
            }
            return parameterSet;
        }

        public object Current
        {
            get
            {
                return parameterList.GetEnumerator().Current;
            }
        }

        public bool MoveNext()
        {
            return parameterList.GetEnumerator().MoveNext();
        }

        public void Reset()
        {

        }

        public bool HasValue(string name)
        {
            foreach (Parameter p in parameterList)
            {
                if (p.Name == name)
                {
                    return true;
                }
            }
            return false;
        }

        public void SetValue(string name, object value)
        {
            foreach (Parameter p in parameterList)
            {
                if (p.Name == name)
                {
                    p.Value = value;
                    return;
                }
            }
            AddValue(name, value);
        }

        public object GetValue(string name)
        {
            foreach (Parameter p in parameterList)
            {
                if (p.Name == name)
                {
                    return p.Value;
                }
            }
            throw new ApplicationException("parameter '" + name + "' not found");
        }

        public object GetValue(string name, object defaultValue)
        {
            foreach (Parameter p in parameterList)
            {
                if (p.Name == name)
                {
                    return p.Value;
                }
            }
            return defaultValue;
        }

        public void AddValue(string name, object value)
        {
            foreach (Parameter p in parameterList)
            {
                if (p.Name == name)
                {
                    throw new ArgumentException("Paramter with that name already exists");
                }
            }
            parameterList.Add(new Parameter(name, value));
        }
    }
}
