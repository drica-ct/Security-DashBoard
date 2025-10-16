#include "../../include/security.h"

static t_severity	parse_grade(char *str)
{
	t_severity  tmp;

	if (ft_strcmp(str, "\"HIGH\":", 7) == 0)
		tmp = HIGH;
	else if (ft_strcmp(str, "\"MID\":", 6) == 0)
		tmp = MID;
	else if (ft_strcmp(str, "\"LOW\":", 6) == 0)
		tmp = LOW;
	else if (ft_strcmp(str, "\"CRITICAL\":", 11) == 0)
		tmp = CRITICAL;

	free(str);
	return (tmp);
}

static void	parse_refs(t_vulnerabilities *vuln, int fd)
{
	vuln->references = malloc(X * sizeof(char **));
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

		// TODO add_to_matrix(vuln->references, buff);

		free(line);
		free(buff);
	}
}

static void	parse_vuln(t_results *result, int fd)
{
	t_vulnerabilities   *tmp_vuln = malloc(1 * sizeof(t_vulnerabilities));

	while (1)
	{
		char *line = get_next_line(fd); // TODO trazer o get_next_line
		if (!line)
			break ;
		char *buff = trim_whitespace(line);
		if (ft_strcmp(buff, "}", 1) == 0)
		{
			free(line);
			free(buff);
			break ;
		}

		if (ft_strcmp(buff, "\"VulnerabilityID\":", 18) == 0)
		{
			tmp_vuln->id = ft_substr(buff, 19, ft_strlen(buff));
		}
		else if (ft_strcmp(buff, "\"PkgName\":", 10) == 0)
		{
			tmp_vuln->pkg_name = ft_substr(buff, 11, ft_strlen(buff));
		}
		else if (ft_strcmp(buff, "\"InstalledVersion\":", 19) == 0)
		{
			tmp_vuln->install_version = ft_substr(buff, 20, ft_strlen(buff));
		}
		else if (ft_strcmp(buff, "\"FixedVersion\":", 15) == 0)
		{
			tmp_vuln->fixed_version = ft_substr(buff, 16, ft_strlen(buff));
		}
		else if (ft_strcmp(buff, "\"Severity\":", 11) == 0)
		{
			tmp_vuln->grade = parse_grade(ft_substr(buff, 12, ft_strlen(buff)));
		}
		else if (ft_strcmp(buff, "\"Title\":", 8) == 0)
		{
			tmp_vuln->title = ft_substr(buff, 9, ft_strlen(buff));
		}
		else if (ft_strcmp(buff, "\"Description\":", 14) == 0)
		{
			tmp_vuln->description = ft_substr(buff, 15, ft_strlen(buff));
		}
		else if (ft_strcmp(buff, "\"References\":", 13) == 0)
		{
			parse_refs(&tmp_vuln, fd);
		}

		free(line);
		free(buff);
	}
    // TODO adicionar a lista (result->vuln_list)
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

		if (ft_strcmp(buff, "\"Target\":", 9) == 0)
		{
			result->target = ft_substr(buff, 10, ft_strlen(buff));
		}
		else if (ft_strcmp(buff, "\"Class\":", 8) == 0)
		{
			result->pc_class = ft_substr(buff, 9, ft_strlen(buff));
		}
		else if (ft_strcmp(buff, "\"Type\":", 7) == 0)
		{
			result->type = ft_substr(buff, 8, ft_strlen(buff));
		}
		else if (ft_strcmp(buff, "\"Vulnerabilities\":", 18) == 0)
		{
			parse_vuln(&result, fd);
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

		if (ft_strcmp(buff, "\"Results\":", 10) == 0)
			parse_results(&result, fd);

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