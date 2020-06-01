namespace Lab2
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.algo1 = new System.Windows.Forms.Button();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.algo2 = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.button5 = new System.Windows.Forms.Button();
            this.button6 = new System.Windows.Forms.Button();
            this.button7 = new System.Windows.Forms.Button();
            this.button8 = new System.Windows.Forms.Button();
            this.open_port = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // algo1
            // 
            this.algo1.Location = new System.Drawing.Point(72, 107);
            this.algo1.Name = "algo1";
            this.algo1.Size = new System.Drawing.Size(105, 39);
            this.algo1.TabIndex = 0;
            this.algo1.Text = "Algo1";
            this.algo1.UseVisualStyleBackColor = true;
            this.algo1.Click += new System.EventHandler(this.algo1_Click);
            // 
            // timer
            // 
            this.timer.Interval = 1000;
            this.timer.Tick += new System.EventHandler(this.timer_Tick);
            // 
            // algo2
            // 
            this.algo2.Location = new System.Drawing.Point(594, 107);
            this.algo2.Name = "algo2";
            this.algo2.Size = new System.Drawing.Size(105, 39);
            this.algo2.TabIndex = 1;
            this.algo2.Text = "Algo2";
            this.algo2.UseVisualStyleBackColor = true;
            this.algo2.Click += new System.EventHandler(this.algo2_Click);
            // 
            // button1
            // 
            this.button1.BackColor = System.Drawing.SystemColors.Desktop;
            this.button1.Location = new System.Drawing.Point(72, 306);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(39, 39);
            this.button1.TabIndex = 2;
            this.button1.UseVisualStyleBackColor = false;
            // 
            // button2
            // 
            this.button2.BackColor = System.Drawing.SystemColors.Desktop;
            this.button2.Location = new System.Drawing.Point(151, 306);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(39, 39);
            this.button2.TabIndex = 3;
            this.button2.UseVisualStyleBackColor = false;
            // 
            // button3
            // 
            this.button3.BackColor = System.Drawing.SystemColors.Desktop;
            this.button3.Location = new System.Drawing.Point(237, 306);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(39, 39);
            this.button3.TabIndex = 4;
            this.button3.UseVisualStyleBackColor = false;
            // 
            // button4
            // 
            this.button4.BackColor = System.Drawing.SystemColors.Desktop;
            this.button4.Location = new System.Drawing.Point(318, 306);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(39, 39);
            this.button4.TabIndex = 5;
            this.button4.UseVisualStyleBackColor = false;
            // 
            // button5
            // 
            this.button5.BackColor = System.Drawing.SystemColors.Desktop;
            this.button5.Location = new System.Drawing.Point(398, 306);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(39, 39);
            this.button5.TabIndex = 6;
            this.button5.UseVisualStyleBackColor = false;
            // 
            // button6
            // 
            this.button6.BackColor = System.Drawing.SystemColors.Desktop;
            this.button6.Location = new System.Drawing.Point(660, 306);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(39, 39);
            this.button6.TabIndex = 7;
            this.button6.UseVisualStyleBackColor = false;
            // 
            // button7
            // 
            this.button7.BackColor = System.Drawing.SystemColors.Desktop;
            this.button7.Location = new System.Drawing.Point(568, 306);
            this.button7.Name = "button7";
            this.button7.Size = new System.Drawing.Size(39, 39);
            this.button7.TabIndex = 8;
            this.button7.UseVisualStyleBackColor = false;
            // 
            // button8
            // 
            this.button8.BackColor = System.Drawing.SystemColors.Desktop;
            this.button8.Location = new System.Drawing.Point(479, 306);
            this.button8.Name = "button8";
            this.button8.Size = new System.Drawing.Size(39, 39);
            this.button8.TabIndex = 9;
            this.button8.UseVisualStyleBackColor = false;
            // 
            // open_port
            // 
            this.open_port.Location = new System.Drawing.Point(290, 107);
            this.open_port.Name = "open_port";
            this.open_port.Size = new System.Drawing.Size(203, 39);
            this.open_port.TabIndex = 10;
            this.open_port.Text = "Open Port";
            this.open_port.UseVisualStyleBackColor = true;
            this.open_port.Click += new System.EventHandler(this.open_port_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.open_port);
            this.Controls.Add(this.button8);
            this.Controls.Add(this.button7);
            this.Controls.Add(this.button6);
            this.Controls.Add(this.button5);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.algo2);
            this.Controls.Add(this.algo1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button algo1;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Timer timer;
        private System.Windows.Forms.Button algo2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.Button button6;
        private System.Windows.Forms.Button button7;
        private System.Windows.Forms.Button button8;
        private System.Windows.Forms.Button open_port;
    }
}

