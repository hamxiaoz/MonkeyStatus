using System;
using System.Collections.Generic;
using System.Text;
using Growl.Connector;

namespace Zurassic
{
    public class GrowlNotifier
    {
        private GrowlConnector growl;
        private NotificationType notificationType;
        private Growl.Connector.Application application;
        private string SAMPLENOTIFICATIONTYPE = "SAMPLE_NOTIFICATION";
        private Boolean _isNotificationActive = false;

        public GrowlNotifier()
        {
            this.notificationType = new NotificationType(SAMPLENOTIFICATIONTYPE, "Sample Notification");

            this.growl = new GrowlConnector();

            this.growl.NotificationCallback += new GrowlConnector.CallbackEventHandler(growl_NotificationCallback);

            // set this so messages are sent in plain text (easier for debugging)
            this.growl.EncryptionAlgorithm = Cryptography.SymmetricAlgorithmType.PlainText;

            RegisterToGrowl();
        }

        public void SendNotification()
        {
            if (!_isNotificationActive)
            {
                CallbackContext callbackContext = new CallbackContext("some fake information", "fake data");

                Notification notification = new Notification(this.application.Name, this.notificationType.Name, DateTime.Now.Ticks.ToString(), "title", "content");
                _isNotificationActive = true;
                this.growl.Notify(notification, callbackContext);
            }
        }

        private void RegisterToGrowl()
        {
            this.application = new Growl.Connector.Application("MonkeyStatus");

            this.growl.Register(application, new NotificationType[] { notificationType });
        }

        private void growl_NotificationCallback(Response response, CallbackData callbackData, object state)
        {
            _isNotificationActive = false;
            //string text = String.Format("Response Type: {0}\r\nNotification ID: {1}\r\nCallback Data: {2}\r\nCallback Data Type: {3}\r\n", callbackData.Result, callbackData.NotificationID, callbackData.Data, callbackData.Type);
            //MessageBox.Show(text, "Callback received", MessageBoxButtons.OK, MessageBoxIcon.Information, MessageBoxDefaultButton.Button1);
        }
    }
}
