/*# Scan a Docker image for vulnerabilities
trivy image nginx:latest

# Scan source code for IaC misconfigurations
trivy config ./my-terraform-code
*/

//Exemplo muito duvidoso
// TODO = Por fazer, ou revisitar
// REDO = Reavaliar ou refazer o segmento

#include "../include/security.h"

int main(void)
{
	if (access("trivy", F_OK) != 0)
	{
		printf("Trivy is not installed in this unit. Please install Trivy before proceeding\n");
		return 1;
	}

	t_results result;
	// TODO Preciso escrever init_results()

	// TODO Definir isto em duas threads

	// Define the image to scan
	const char *image = "nginx:latest";
	const char *json_file = "security/report.json"; // TODO definir nome da pasta

	// Construct the command string // REDO
	char command[256];
	snprintf(command, sizeof(command), "./src/scan.sh %s", image);

	// Run the command // REDO
	if (system(command) != 0)
	{
		fprintf(stderr, "Error: Trivy scan failed.\n");
		return 1;
	}

	parse_json(&result, json_file);

	// Open the results file // REDO
	FILE *fp = fopen(json_file, "r");
	if (!fp)
	{
		perror("Failed to open results file");
		return 1;
	}

	// Open a new file // REDO
	FILE *out = fopen("./report.md", "w");
	if (!out)
	{
		perror("Failed to open output file");
		fclose(fp);
		return 1;
	}

	// Process or save the results (here we just copy to the second file) // REDO
	char buffer[1024];
	size_t n;
	while ((n = fread(buffer, 1, sizeof(buffer), fp)) > 0)
	{
		fwrite(buffer, 1, n, out);
	}

	fclose(fp);
	fclose(out);

	//printf("Scan complete. Results saved to ./report.md\n");
	return 0;
}
