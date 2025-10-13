#include "../../include/security.h"

static void	parse_vuln(t_results *result, int fd)
{
	; // TODO escrever funcao
}

static void	parse_results(t_results *result, int fd)
{
	while (1)
	{
		char *line = get_next_line(fd); // TODO trazer o get_next_line
		if (!line)
			break ;
		char *buff = trim_whitespace(line);
		if (ft_strcmp(buff, "]", 1) == 0)
		{
			free(line);
			free(buff);
			break ;
		}

		if (ft_strcmp(buff, "Target:", 7) == 0) // TODO As aspas vao estar no json?
		{
			result->target = ft_substr(buff, 8, ft_strlen(buff));
		}
		else if (ft_strcmp(buff, "Class:", 6) == 0) // TODO As aspas vao estar no json?
		{
			result->pc_class = ft_substr(buff, 7, ft_strlen(buff));
		}
		else if (ft_strcmp(buff, "Type:", 5) == 0) // TODO As aspas vao estar no json?
		{
			result->type = ft_substr(buff, 6, ft_strlen(buff));
		}
		else if (ft_strcmp(buff, "Vulnerabilities:", 16) == 0) // TODO As aspas vao estar no json?
		{
			parse_vuln(&result, fd); // TODO escrever funcao
		}

		free(line);
		free(buff);
	}
}

void	parse_json(t_results *result, const char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_map("Cannot open .json file"); // TODO escrever error_exit e afins

	while (1)
	{
		char *line = get_next_line(fd); // TODO trazer o get_next_line
		if (!line)
			break ;
		char *buff = trim_whitespace(line);
		if (ft_strcmp(buff, "]", 1) == 0)
		{
			free(line);
			free(buff);
			break ;
		}

		if (ft_strcmp(buff, "Results:", 8) == 0) // TODO As aspas vao estar no json?
			parse_results(&result, fd); // TODO escrever funcao

		free(line);
		free(buff);
	}
	close(fd);
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