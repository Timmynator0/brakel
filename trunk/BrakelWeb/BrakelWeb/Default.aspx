<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="BrakelWeb.Temperature" %>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN" >
<html>
	<head>
<title>"Historische Gegevens"</title>
	</head>
	<body>
		<form id="PieChart" method="post" runat="server">
			<table class="sampleTable">
				<tr>
					<td width="412" class="tdchart">
							<asp:chart id="Chart1" runat="server" ImageLocation="~/TempImages/ChartPic_#SEQ(300,3)" imagetype="Png" BackColor="WhiteSmoke" BorderWidth="2" BackGradientStyle="TopBottom" BackSecondaryColor="White" Palette="BrightPastel" BorderlineDashStyle="Solid" BorderColor="26, 59, 105" Height="600px" Width="1000px">
								<titles>
									<asp:title ShadowColor="32, 0, 0, 0" Font="Trebuchet MS, 12pt, style=Bold" ShadowOffset="3" Text="Historische Data" ForeColor="26, 59, 105"></asp:title>
								</titles>
								<legends>
									<asp:legend Enabled="True" IsTextAutoFit="False" Name="Default" BackColor="Transparent" Font="Trebuchet MS, 8.25pt, style=Bold"></asp:legend>
								</legends>
								<borderskin skinstyle="Emboss"></borderskin>
								<series>
									<asp:series Name="Temperature" ChartType="FastLine" ShadowColor="Black" BorderColor="180, 26, 59, 105"></asp:series>
									<asp:series Name="CO2" ChartType="FastLine" ShadowColor="Black" BorderColor="180, 26, 59, 105" Color="160,32,240"></asp:series>
                                    <asp:series Name="Humidity" ChartType="FastLine" ShadowColor="Black" BorderColor="180, 26, 59, 105" Color="224,0,0"></asp:series>
                                    <asp:series Name="Light Intensity" ChartType="FastLine" ShadowColor="Black" BorderColor="180, 26, 59, 105" Color="124, 252,0"></asp:series>
								</series>
								<chartareas>
									<asp:chartarea Name="ChartArea1" BorderColor="64, 64, 64, 64" BorderDashStyle="Solid" BackSecondaryColor="White" BackColor="Gainsboro" ShadowColor="Transparent" BackGradientStyle="TopBottom">
										<area3dstyle Rotation="10" perspective="10" Inclination="15" IsRightAngleAxes="False" wallwidth="0" IsClustered="False"></area3dstyle>
										<axisy linecolor="64, 64, 64, 64" IsLabelAutoFit="False">
											<labelstyle font="Trebuchet MS, 8.25pt, style=Bold" />
											<majorgrid linecolor="64, 64, 64, 64" />
										</axisy>
										<axisx linecolor="64, 64, 64, 64" IsLabelAutoFit="False">
											<labelstyle font="Trebuchet MS, 8.25pt, style=Bold" />
											<majorgrid linecolor="64, 64, 64, 64" />
										</axisx>
									</asp:chartarea>
								</chartareas>
							</asp:chart>
					</td>
				</tr>
			</table>
		</form>
	</body>
</html>
