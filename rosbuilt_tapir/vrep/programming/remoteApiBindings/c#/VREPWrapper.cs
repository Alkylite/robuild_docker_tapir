﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace remoteApiNETWrapper
{
    public static class VREPWrapper
    {
        [DllImport("remoteApi.dll")]
        public static extern void simxFinish(int clientID);

        [DllImport("remoteApi.dll")]
        public static extern int simxGetConnectionId(int clientID);

        [DllImport("remoteApi.dll")]
        public static extern simx_return simxGetFloatSignal(int clientID, string signalName, ref float value, simx_opmode opmode);

        [DllImport("remoteApi.dll")]
        public static extern simx_return simxGetIntegerSignal(int clientID, string signalName, ref int value, simx_opmode opmode);

        public static int simwGetIntegerSignal(int clientID, string signalName)
        {
            int v = -1;
            simxGetIntegerSignal(clientID, signalName, ref v, simx_opmode.streaming);
            Thread.Sleep(150);
            simxGetIntegerSignal(clientID, signalName, ref v, simx_opmode.buffer);
            return v;
        }

        [DllImport("remoteApi.dll")]
        public static extern simx_return simxSetStringSignal(int clientID, string signalName, string value, int length, simx_opmode opmode);

        [DllImport("remoteApi.dll")]
        public static extern simx_return simxGetStringSignal(int clientID, string signalName, ref IntPtr pointerToValue, ref int signalLength, simx_opmode opmode);

        public static string simwGetStringSignal(int clientID, string signalName)
        {
            IntPtr p = IntPtr.Zero;
            var l1 = 0;
            var l2 = 0;
            var e = simxGetStringSignal(clientID, signalName, ref p, ref l1, simx_opmode.streaming);
            Thread.Sleep(150);
            e = simxGetStringSignal(clientID, signalName, ref p, ref l2, simx_opmode.buffer);
            Console.WriteLine("Signal {0} -> {1}/{2}", signalName, l1, l2);
            if (e == simx_return.noerror && p != IntPtr.Zero)
            {
                var s = Marshal.PtrToStringAnsi(p, l2);
                Marshal.Release(p);
                return s;
            }
            return "";
        }

        [DllImport("remoteApi.dll")]
        public static extern simx_return simxGetAndClearStringSignal(int clientID, string signalName, ref IntPtr pointerToValue, ref int signalLength, simx_opmode opmode);

        [DllImport("remoteApi.dll")]
        public static extern simx_return simxGetJointPosition(int clientID, int jointHandle, ref float targetPosition, simx_opmode opmode);

        [DllImport("remoteApi.dll")]
        public static extern simx_return simxGetObjectIntParameter(int clientID, int objectHandle, int parameterID, ref int parameterValue, simx_opmode opmode);

        [DllImport("remoteApi.dll")]
        public static extern simx_return simxGetObjectFloatParameter(int clientID, int objectHandle, int parameterID, ref float parameterValue, simx_opmode opmode);

        [DllImport("remoteApi.dll")]
        public static extern simx_return simxGetObjectOrientation(int clientID, int jointHandle, int relativeToHandle, float[] orientations, simx_opmode opmode);

        [DllImport("remoteApi.dll")]
        public static extern simx_return simxGetObjectPosition(int clientID, int jointHandle, int relativeToHandle, float[] positions, simx_opmode opmode);

        [DllImport("remoteApi.dll")]
        public static extern simx_return simxPauseCommunication(int cliendID, int pause);

        [DllImport("remoteApi.dll")]
        public extern static simx_return simxReadProximitySensor(int clientID, int sensorHandle,
                                                         ref char detectionState, float[] detectionPoint, ref int objectHandle, float[] normalVector, simx_opmode opmode);

        [DllImport("remoteApi.dll")]
        public static extern simx_return simxSetJointTargetPosition(int clientID, int jointHandle, float targetPosition, simx_opmode opmode);

        [DllImport("remoteApi.dll")]
        public static extern simx_return simxSetJointTargetVelocity(int clientID, int jointHandle, float velocity, simx_opmode opmode);

        [DllImport("remoteApi.dll")]
        public static extern simx_return simxSetObjectFloatParameter(int clientID, int objectHandle, int parameterID, float parameterValue, simx_opmode opmode);

        [DllImport("remoteApi.dll")]
        public static extern simx_return simxSetObjectIntParameter(int clientID, int objectHandle, int parameterID, int parameterValue, simx_opmode opmode);

        [DllImport("remoteApi.dll")]
        public static extern int simxStart(string ip, int port, bool waitForConnection, bool reconnectOnDisconnect, int timeoutMS, int cycleTimeMS);

        [DllImport("remoteApi.dll")]
        public static extern simx_return simxGetUIEventButton(int clientID, int uiHandle, ref int uiEventButtonID, IntPtr aux, simx_opmode opmode);

        [DllImport("remoteApi.dll")]
        // public static extern simx_return simxGetUIHandle(int clientID, string uiName, out int handle, simx_opmode opmode);
        public static extern simx_return simxGetUIHandle(int clientID, string uiName, IntPtr p, simx_opmode opmode);

        [DllImport("remoteApi.dll")]
        public static extern simx_return simxGetObjectHandle(int clientID, string objectName, out int handle, simx_opmode opmode);
    }
}