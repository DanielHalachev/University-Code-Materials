using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Drawing;

namespace FractalRenderer
{
    public class RenderResult : IAsyncResult
    {
        public delegate void RenderComplete(Bitmap bmp, int ErrorCode);
        public delegate void RenderStatus(float pcnt);
        
        private bool isCompleted = false;
        private object asyncstate = new object();
        private WaitHandle waitHandle = new AutoResetEvent(false);
          
        public object AsyncState
        {
            get
            {
                return asyncstate;
            }
            set
            {
                asyncstate = value;
            }
        }

        public WaitHandle AsyncWaitHandle
        {
            get
            {
                return waitHandle;
            }
        }

        public bool CompletedSynchronously
        {
            get
            {
                return false;
            }
        }

        public bool IsCompleted
        {
            get
            {
                return isCompleted;
            }
            set
            {
                isCompleted = value;
            }
        }
    }
}
