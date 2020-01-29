#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE* port_open;
	int port_number,port_start,port_end,result,ret,auto_mode;
	char server_ip[40],run[60];
	printf("请输入用于端口扫描的服务器地址：");
	scanf("%s", server_ip);
	printf("请输入起始端口号与终止端口号（如22 65535）：");
	scanf("%d %d", &port_start,&port_end);
	printf("是否进入自动模式（是=1 否=0）：");
	scanf("%d", &auto_mode);
	if (port_start > port_end) {
		ret = port_end;
		port_end = port_start;
		port_start = ret;
		printf("\n起始端口与终止端口相反，自动反向重置！\n");
	}
	if (port_start < 20||port_start+abs(port_start)==0) {
		port_start = 20;
		printf("\n起始端口过小，自动重置为20！\n");
	}
	if (port_end > 65535||port_end+abs(port_end)==0) {
		port_end = 65535;
		printf("\n终止端口过大，自动重置为65535！\n");
	}
	system("timeout /t 3 /nobreak");
	port_open = fopen("port_open.txt", "a");
	fprintf(port_open, "\n-------------------------------------\n");
	fprintf(port_open, "服务器地址：%s\n",server_ip);
	fprintf(port_open, "可用端口号：");
	fclose(port_open);
	for (port_number = port_start; port_number <= port_end; port_number++) {
		system("cls");
		printf("----------------------------------------------------------\n");
		printf("正在测试服务器地址：%s 端口：%d\n",server_ip,port_number);
		printf("----------------------------------------------------------\n");
		sprintf(run, "tcping %s %d", server_ip, port_number);
		result = system(run);
		if (result == 0) {
			printf("\n------------------------------------------\n");
			printf("端口状态：开放\n");
			printf("------------------------------------------\n");
			port_open = fopen("port_open.txt", "a");
			fprintf(port_open, " %d,",port_number);
			fclose(port_open);
		}
		else {
			printf("\n------------------------------------------\n");
			printf("端口状态：封锁\n");
			printf("------------------------------------------\n");
		}
		if(auto_mode==0)system("timeout /t 3 /nobreak");
	}
	system("cls");
	port_open = fopen("port_open.txt", "a");
	fprintf(port_open, "\n-------------------------------------\n");
	fclose(port_open);
	printf("测试完成！结果请参看测试报告！\n");
	system("notepad port_open.txt");
	return 0;
}