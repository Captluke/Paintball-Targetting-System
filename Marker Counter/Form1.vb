
Imports System
Imports System.IO.Ports

Public Class Form1
    Dim comport As String
    Dim receiveddata As String = ""
    Dim timer = 1
    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Timer1.Enabled = False
        comport = ""
        For Each sp As String In My.Computer.Ports.SerialPortNames
            ComboBox1.Items.Add(sp)
        Next
    End Sub

    Private Sub ComboBox1_SelectedIndexChanged(sender As Object, e As EventArgs) Handles ComboBox1.SelectedIndexChanged
        If (ComboBox1.SelectedItem <> "") Then
            comport = ComboBox1.SelectedItem
            'MsgBox(comport)
        End If
    End Sub

    Private Sub Connect_Click(sender As Object, e As EventArgs) Handles Connect.Click
        If (Connect.Text = "Connect") Then
            If (comport <> "") Then
                SerialPort1.Close()
                SerialPort1.PortName = comport
                SerialPort1.BaudRate = 9600
                SerialPort1.DataBits = 8
                SerialPort1.Parity = Parity.None
                SerialPort1.StopBits = StopBits.One
                SerialPort1.Handshake = Handshake.None
                SerialPort1.Encoding = System.Text.Encoding.Default
                SerialPort1.ReadTimeout = 10000
                SerialPort1.DtrEnable = True
                TextBox1.Text = 0
                SerialPort1.Open()
                Connect.Text = "Disconnect"

            Else
                MsgBox("Please select COM port first !")
            End If
        Else
            SerialPort1.Close()
            Connect.Text = "Connect"
            Timer1.Enabled = False
        End If
    End Sub

    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick
        receiveddata = Receiveserialdata()
        RichTextBox1.Text = receiveddata
        RichTextBox1.SelectionAlignment = HorizontalAlignment.Center

    End Sub

    Function Receiveserialdata() As String
        Dim incoming As String
        Try
            incoming = SerialPort1.ReadExisting()
            If incoming Is Nothing Then
                Return "Nothing !" & vbCrLf
            Else
                Return incoming
            End If
        Catch ex As Exception
            Return "Error Message : Can't read Serial Port"

        End Try
    End Function

    Private Sub Timer2_Tick(sender As Object, e As EventArgs) Handles Timer2.Tick
        TextBox1.Text = TextBox1.Text + 1

    End Sub

    Private Sub Start_Click(sender As Object, e As EventArgs) Handles Start.Click
        If (Connect.Text = "Disconnect" And timer = 1) Then
            Timer2.Start()
            Timer1.Enabled = True
            Start.BackgroundImage = My.Resources._Stop
            Start.ImageAlign = ContentAlignment.MiddleCenter
            Start.FlatStyle = FlatStyle.Popup
            Start.Anchor = AnchorStyles.Left
            Start.Anchor = AnchorStyles.Right
            Start.Anchor = AnchorStyles.Top
            Start.Anchor = AnchorStyles.Bottom
            Start.BackgroundImageLayout = ImageLayout.Zoom
            Start.AutoSizeMode = AutoSizeMode.GrowAndShrink
            TextBox1.Text = 0

            timer = 0

        ElseIf (Connect.Text = "Disconnect" And timer = 0) Then
            Timer2.Stop()
            Start.BackgroundImage = My.Resources.red_start_png_5
            Start.ImageAlign = ContentAlignment.MiddleCenter
            Start.FlatStyle = FlatStyle.Popup
            Start.Anchor = AnchorStyles.Left
            Start.Anchor = AnchorStyles.Right
            Start.Anchor = AnchorStyles.Top
            Start.Anchor = AnchorStyles.Bottom
            Start.BackgroundImageLayout = ImageLayout.Zoom
            Start.AutoSizeMode = AutoSizeMode.GrowAndShrink
            Timer1.Enabled = False
            timer = 1
            SerialPort1.DtrEnable = True

        Else
            MsgBox("Please select COM port first !")
        End If

    End Sub


End Class
