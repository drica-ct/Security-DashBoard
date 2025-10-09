/*# Scan a Docker image for vulnerabilities
trivy image nginx:latest

# Scan source code for IaC misconfigurations
trivy config ./my-terraform-code
*/

//Exemplo muito duvidoso
// TODO = Por fazer, ou revisitar
// REDO = Reavaliar ou refazer o segmento

#include "../include/security.h"
#include <stdio.h>
#include <stdlib.h>

static size_t	ft_strlen(const char *str)
{
	size_t	l;

	l = 0;
	while (str[l] != '\0')
		l++;
	return (l);
}

static bool	ft_isdelim(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\0'
		|| c == '\v' || c == '\f' || c == '\r')
		return (true);
	else
		return (false);
}

static char	*trim_whitespace(const char *str)
{
	unsigned int	i = 0;
	unsigned int	j = ft_strlen(str);
	unsigned int	k = 0;
	char			*dest;

	while(ft_isdelim(str[i]))
		i++;

	while(ft_isdelim(str[j]))
		j--;

	dest = (char *)malloc((j - i + 2) * sizeof(char));
	if (!dest)
		return (NULL);

	while(i + k <= j)
	{
		dest[k] = str[i + k];
		k++;
	}
	dest[k] = '\0';

	return (dest);
}

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		r;

	i = 0;
	r = 0;
	while (s1[i] != '\0' && i < n && r == 0)
	{
		r = (unsigned char)s1[i] - (unsigned char)s2[i];
		i++;
	}
	if (r == 0 && ft_strlen(s1) < ft_strlen(s2) && i < n)
	{
		while (s2[i] != '\0' && i < n)
		{
			r -= (unsigned char)s2[i];
			i++;
		}
	}
	if (r > 0)
		r /= r;
	else if (r < 0)
		r /= -r;
	return (r);
}

static void	parse_line(t_results *result, char *line)
{
	// TODO As aspas vao estar no json?
	if (ft_strcmp(line, "Target:", 7) != 0)
	{
		; // TODO para cada linha, guardar info relevante;
	}
}

static void	parse_json(t_results *result, const char *file)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_map("Cannot open .json file"); // TODO escrever error_exit e afins
	while (1)
	{
		char	*buff;

		line = get_next_line(fd); // TODO trazer o get_next_line
		if (!line)
			break ;
		buff = trim_whitespace(line);
		if (!ft_isemptystr(buff))
			parse_line(&result, line); // TODO escrever funcao
		free(line);
		free(buff);
	}
	close(fd);
}

int main(void)
{
	if (access(trivy, F_OK) != 0)
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


/*Expected "security/report.json" file:

{
  "SchemaVersion": 2,
  "ArtifactName": "nginx:latest",
  "ArtifactType": "container_image",
  "Metadata": {
    "OS": {
      "Family": "debian",
      "Name": "11.5"
    },
    "ImageID": "sha256:abc123...",
    "DiffIDs": [
      "sha256:def456...",
      "sha256:ghi789..."
    ]
  },
  "Results": [
    {
      "Target": "nginx:latest (debian 11.5)",
      "Class": "os-pkgs",
      "Type": "debian",
      "Vulnerabilities": [
        {
          "VulnerabilityID": "CVE-2022-12345",
          "PkgName": "libc-bin",
          "InstalledVersion": "2.31-13+deb11u3",
          "FixedVersion": "2.31-13+deb11u4",
          "Severity": "HIGH",
          "Title": "Buffer overflow in libc",
          "Description": "A buffer overflow vulnerability in libc...",
          "References": [
            "https://security-tracker.debian.org/tracker/CVE-2022-12345",
            "https://nvd.nist.gov/vuln/detail/CVE-2022-12345"
          ]
        },
        {
          "VulnerabilityID": "CVE-2021-99999",
          "PkgName": "openssl",
          "InstalledVersion": "1.1.1k-1",
          "FixedVersion": "1.1.1l-1",
          "Severity": "MEDIUM",
          "Title": "SSL certificate validation issue",
          "Description": "Improper validation in OpenSSL...",
          "References": [
            "https://www.openssl.org/news/secadv/2021.txt"
          ]
        }
      ]
    }
  ]
}
*/