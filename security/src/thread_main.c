#include "../include/security.h"

typedef struct s_trivy_job
{
	const char *image;
	const char *json_file;
}	t_trivy_job;

static void *thread_run_trivy(void *arg)
{
	t_trivy_job *job = (t_trivy_job *)arg;

	printf("Starting scan for image: %s\n", job->image);
	run_trivy(job->image, job->json_file);
	printf("Completed scan for image: %s → %s\n", job->image, job->json_file);
}

int main(void)
{

	if (access("trivy", F_OK) != 0) {
		printf("Trivy is not installed in this unit. Please install Trivy before proceeding.\n");
		return 1;
	}

	t_trivy_job job1 =
	{
		.image = "nginx:latest",
		.json_file = "security/nginx_report.json"
	};
	t_trivy_job job2 =
	{
		.image = "python:3.9",
		.json_file = "security/python_report.json"
	};

	pthread_t t1, t2;

	if (pthread_create(&t1, NULL, thread_run_trivy, &job1) != 0)
	{
		perror("Failed to create thread 1 (nginx)");
		return (1);
	}
	if (pthread_create(&t2, NULL, thread_run_trivy, &job2) != 0)
	{
		perror("Failed to create thread 2 (python)");
		return (1);
	}

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	printf("Both scans completed.\n");

	return (0);
}
