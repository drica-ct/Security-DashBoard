resource "aws_eks_cluster" "my_cluster" {
    name = "my-cluster"
    role_arn = 

    vpc_config {
        subnet_ids = [
            aws_subnet.private_subnet_1.id,
            aws_subnet.private_subnet_2.id
        ]
    }
}

resource "aws_eks_node_group" "my_node_group" {
    cluster_name = aws_eks_cluster.my_cluster.name
    node_group_name = "node-group"
    node_role_arn = 
    subnet_ids = [
        aws_subnet.private_subnet1.id,
        aws_subnet.private_subnet2.id
    ]

    scaling_config {
        desired_size = 1
        max_size = 3
        min_size = 1
    }

    instance_types = ["t3.medium"]
}