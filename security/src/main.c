#include "../include/security.h"

typedef struct s_trivy_job
{
	const char *image;
	const char *json_file;
}	t_trivy_job;

static void run_trivy(const char *image, const char *json_file, t_results *result)
{
	// Construct the command string // REDO
	char command[256];
	snprintf(command, sizeof(command), "./src/scan.sh %s", image);

	// Run the command // REDO
	if (system(command) != 0)
	{
		fprintf(stderr, "Error: Trivy scan failed.\n");
		return 1;
	}

	//parse_json(&result, json_file);
}

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
		.json_file = "./scans/IMAGE/report.json" // TODO corrigir o nome da IMAGE quando finalizado
	};
	t_trivy_job job2 =
	{
		.image = "python:3.9",
		.json_file = "./scans/IMAGE/report.json" // TODO corrigir o nome da IMAGE quando finalizado
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
